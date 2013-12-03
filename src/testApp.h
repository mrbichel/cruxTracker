#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Beta.h"
#include "Tracker.h"



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
        ofxPanel gui;
    
    
        Beta * beta;
        Tracker * tracker;
        ofParameterGroup parameters;

        
        ofVec2f pressPos;
        float dragDist;
        bool isDrag = false;
    
    
};
