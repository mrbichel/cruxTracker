//
//  Tracker.h
//  cruxTracker
//
//  Created by pd on 03/12/2013.
//
//

#pragma once
#include "ofxOpenCv.h"

struct blob {
    int frame;
    float height;
    int ID;
    float pX;
    float pY;
    float width;
    float x;
    float y;
    
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
        
        //colorImg.draw(20,20);
        //grayImage.draw(360,20);
        grayBg.draw(670,20);
        //grayDiff.draw(360,280);
        
        // then draw the contours:
        
        ofSetHexColor(0xffffff);
        
        // we could draw the whole contour finder
        //contourFinder.draw(20,20);
        
        // or, instead we can draw each blob individually from the blobs vector,
        // this is how to get access to them:
        for (int i = 0; i < contourFinder.nBlobs; i++){
            contourFinder.blobs[i].draw(350,20);
            
            // draw over the centroid if the blob is a hole
            ofSetColor(255);
            if(contourFinder.blobs[i].hole){
                ofDrawBitmapString("pop!",
                                   contourFinder.blobs[i].boundingRect.getCenter().x + 350 ,
                                   contourFinder.blobs[i].boundingRect.getCenter().y + 20);
    
                
            }
        }

        // finally, a report:
        ofSetHexColor(0xffffff);
        ofSetLineWidth(1.f);
        stringstream reportStr;
        reportStr << "press space to capture bg" << endl
        << "threshold " << threshold << endl
        << "videoheight " << videoheight<< endl
        << "videowidth " << videowidth << endl
        << "num blobs found " << contourFinder.nBlobs;
        reportStr << ", fps: " << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 20);

        
        

        }

        
};
