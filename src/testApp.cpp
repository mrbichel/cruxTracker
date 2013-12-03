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
    
    //grayImage.allocate(320,240);
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
    
    ofBackground(0, 0, 0);
    
    
    
	//draw framerate
	ofSetColor(255);
	string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(msg, 10, 20);
    
    
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



