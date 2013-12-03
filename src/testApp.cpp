#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    beta = new Beta();
    tracker = new Tracker();
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(66,66,66);

    beta->setup();
    tracker->setup();
    
}

//--------------------------------------------------------------
void testApp::update(){
    tracker->update();
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
	
        
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key == ' ') {
        debugOn = !debugOn;
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