#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Beta.h"
#include "ofxBullet.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        ofCamera cam;
        float extrusionAmount;
        ofVboMesh mainMesh;
        ofVideoGrabber vidGrabber;
        ofxPanel gui;
    
        ofxCvGrayscaleImage grayBg;
        ofxCvGrayscaleImage grayDiff;
        ofxCvContourFinder contourFinder;
        int 				threshold;
        bool				bLearnBakground;
    
        Beta * beta;
    
        ofParameterGroup parameters;
        
        ofVec2f pressPos;
        float dragDist;
        bool isDrag = false;
    
};
