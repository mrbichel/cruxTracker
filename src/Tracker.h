//
//  Tracker.h
//  cruxTracker
//
//  Created by Johan Bichel Lindegaard on 03/12/2013.
//
//

#pragma once
#include "ofxOpenCv.h"

struct blob {
    
};

struct skeleton {
    
};

class Tracker {
    
public:
    
    ofxCvGrayscaleImage grayBg;
    ofxCvColorImage	colorImg;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder contourFinder;
    ofVideoGrabber vidGrabber;
    int threshold;
    bool bLearnBakground;
    bool bNewFrame = false;
    
    
    int videowidth;
    int videoheight;
    int key;
    void setup() {
        
        grayImage.allocate(320,240);
        grayBg.allocate(320,240);
        grayDiff.allocate(320,240);
        bLearnBakground = true;
        threshold = 80;
        
        //initialize the video grabber
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber(320,240);
        
        //store the width and height for convenience
        videowidth  = vidGrabber.getWidth();
        videoheight = vidGrabber.getHeight();
        

    };
    
    
    void update() {
        vidGrabber.update();
        bNewFrame = vidGrabber.isFrameNew();
    

        
        if (bNewFrame){
            
            colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
            grayImage = colorImg;
        }
        
        if (bLearnBakground == true){
            grayBg = grayImage;
            bLearnBakground = false;
        }
        
        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
    
    };
    
    void debugDraw() {
        grayImage.draw(20,20);
        grayBg.draw(360,20);
        //grayDiff.draw(360,540);
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(20,20);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            if(contourFinder.blobs[i].hole){
                //Draw stuff
                
                contourFinder.blobs[i].boundingRect.getCenter().x ,
                contourFinder.blobs[i].boundingRect.getCenter().y ;
                
                
                
                
            }
        }
        
}

   };