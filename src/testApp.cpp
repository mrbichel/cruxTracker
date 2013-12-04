#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    
    beta = new Beta();
    tracker = new Tracker();
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
    beta->setup();
    tracker->setup();
    
    
    ofBackground( 10, 10, 10);
	
	camera.setPosition(ofVec3f(0, -7.f, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    
	world.setup();
	world.enableGrabbing();
	world.enableDebugDraw();
	world.setCamera(&camera);
	
	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(0, 0, 0), 0.1, .25);
	sphere->add();
	
	box = new ofxBulletBox();
	box->create(world.world, ofVec3f(7, 0, 0), .05, .5, .5, .5);
	box->add();
	
	cone = new ofxBulletCone();
	cone->create(world.world, ofVec3f(-1, -1, .2), .2, .4, 1.);
	cone->add();
	
	capsule = new ofxBulletCapsule();
	capsule->create(world.world, ofVec3f(1, -2, -.2), .4, .8, 1.2);
	capsule->add();
	
	cylinder = new ofxBulletCylinder();
	cylinder->create(world.world, ofVec3f(0, -2.4, 0), .8, .9, 1.8);
	cylinder->add();
	
	ground.create( world.world, ofVec3f(0., 5.5, 0.), 0., 100.f, 1.f, 100.f );
	ground.setProperties(.25, .95);
	ground.add();
    

    
}

//--------------------------------------------------------------
void testApp::update(){
    tracker->update();
    world.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0, 0, 0);
    
    
    
	//draw framerate
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
    
    if(debugOn) {
     tracker->debugDraw();
    }
    
    beta->draw();
    
    if(isDrag) {
        ofSetColor(255,40,40,100);
        ofDrawSphere(pressPos, dragDist);
    }
	
    
    
    glEnable( GL_DEPTH_TEST );
	camera.begin();
	
	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	world.drawDebug();
	
	ofSetColor(100, 100, 100);
	ground.draw();
	
	ofSetColor(225, 225, 225);
	sphere->draw();
	
	ofSetColor(225, 225, 225);
	box->draw();
	
	ofSetColor(225, 225, 225);
	cylinder->draw();
	
	ofSetColor(225, 225, 225);
	capsule->draw();
	
	ofSetColor(225, 225, 225);
	cone->draw();
	
	camera.end();
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
     cout << "keyReleased " << (char)key << endl;
    if(key == 'f') {
        debugOn = !debugOn;
        }
    if(key == ' ') {
        tracker->bLearnBakground = true;
        

    }

    
    
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    if(isDrag) dragDist = ofDist(x, y, pressPos.x, pressPos.y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    isDrag = true;
    pressPos = ofVec2f(x,y);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

    
    isDrag = false;
    cout<<"adding hold"<<endl;
    
    beta->addHold(pressPos, dragDist);
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
