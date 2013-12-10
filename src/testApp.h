#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Beta.h"
#include "Tracker.h"
#include "Meshplane.h"
#include "ofxBullet.h"
#include "ViewMapping.h"

#include "MSAPhysics3D.h"


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
        ofCamera camera;
    
        Beta * beta;
        Tracker * tracker;
    

        enum Mode
            {
            ModeNormal,
            ModeViewMapping
            };
        Mode currentMode;
    
        ofXml settings;
        ofParameterGroup parameters;

        ofParameter<int> intForSlider;
        ofParameter<int> intForSlider1;
        ofParameter<bool> boolForToogle;
        ofParameter<bool> boolForToogle1;
        ofParameter<bool> boolForButton1;
        ofParameter<int> intForSlider2;

        ViewMapping mapping;
        Meshplane meshplane;
    
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
    
    ofLight pointLight;
    ofColor lightColor;
    
    
    msa::physics::World3D		physics;
 
    
   
};
