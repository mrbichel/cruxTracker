#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    beta = new Beta();
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	ofBackground(66,66,66);
	
	//initialize the video grabber
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
    
	//store the width and height for convenience
	int videowidth  = vidGrabber.getWidth();
	int videoheight = vidGrabber.getHeight();
    
    grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
    
	bLearnBakground = true;
	threshold = 30;

    
    beta->setup();
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
       
	//draw framerate
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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



