#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Beta.h"
#include "Tracker.h"
#include "ofxBullet.h"
#include "ViewMapping.h"

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
    
    private:

        ofxPanel gui;
    
        Beta * beta;
        Tracker * tracker;

        enum Mode
            {
            ModeNormal,
            ModeViewMapping
            };
        Mode currentMode;
    
        ofParameterGroup parameters;

        ofParameter<int> intForSlider;
        ofParameter<int> intForSlider1;
        ofParameter<bool> boolForToogle;
        ofParameter<bool> boolForButton1;

        ViewMapping mapping;
    
        ofVec3f gravity;
        ofVec2f pressPos;
        float dragDist;
        bool isDrag = false;
        bool fullscreen = false;
        
        bool debugOn = false;
    
    
    ofxBulletWorldRigid			world;
	ofxBulletBox				ground;
	ofxBulletSphere*			sphere;
	ofxBulletBox*				box;
	ofxBulletCone*				cone;
	ofxBulletCapsule*			capsule;
	ofxBulletCylinder*			cylinder;

    ofCamera camera;

        
};
