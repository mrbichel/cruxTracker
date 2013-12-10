#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    
    beta = new Beta();
    tracker = new Tracker();
    
    beta->setup();
    tracker->setup();
    meshplane.setup();
    mapping.setup();
    
    currentMode = ModeNormal;
    
	ofSetVerticalSync(false);
	ofSetFrameRate(60);
    
    
    parameters.setName("settings");
    parameters.add(intForSlider.set("Blob threshold", 40, 0, 200));
    parameters.add(intForSlider1.set("Gravity", -9.8, -20, 20));
    parameters.add(boolForToogle.set("Fullscreen",false));
    parameters.add(boolForToogle1.set("Debug",false));
    parameters.add(boolForToogle2.set("Draw path",false));
    //Todo make fov
    parameters.add(intForSlider2.set("Fov", 60, 20, 120));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");

	camera.setPosition(ofVec3f(0, -7.f, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	

    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    tracker->threshold = intForSlider;
    debugOn = boolForToogle1;
    pathOn = boolForToogle2;
    
    if (currentMode == ModeNormal) {
        if (boolForToogle == true){
            ofSetFullscreen(true);
        }
            
        else { 
            ofSetFullscreen(false);
        }
        
        meshplane.update();
        tracker->update();
        
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if (currentMode == ModeNormal) {
        ofBackground(0, 0, 0);

        if(isDrag) {
            ofSetColor(255,40,40,100);
            ofDrawSphere(pressPos, dragDist);
        }
        
        mapping.begin();
        
        meshplane.draw();


        beta->draw();
        
        
        mapping.end();

        if(debugOn) {
            tracker->debugDraw();
           
        }
        gui.draw();
        
        ofFill();
        
        // Draw fps;
        ofSetHexColor(0xffffff);
        ofSetLineWidth(1.f);
        stringstream reportStr;
        reportStr << "fps:" << ofGetFrameRate();
        ofDrawBitmapString(reportStr.str(), 20, 20);
    }
    else if (currentMode == ModeViewMapping) {
        mapping.drawInterface();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (currentMode == ModeNormal) {
        if(key == 'f') {
            debugOn = !debugOn;
            cout<<"Debug mode"<<endl;
        }
        if(key == ' ') {
            tracker->bLearnBakground = true;
            cout<<"addet new background"<<endl;
        }
        if(key == OF_KEY_F11) {
            fullscreen = true;
            cout<<"Fullscreen"<<endl;
        }
        if(key == OF_KEY_F10) {
            currentMode = ModeViewMapping;
        }
        
        if(key=='s'){
            settings.serialize(parameters);
            settings.save("settings.xml");
        }
        if(key=='l'){
            settings.load("settings.xml");
            settings.deserialize(parameters);
        }
        
    }
    else if (currentMode == ModeViewMapping) {
        if(key == OF_KEY_F10) {
            currentMode = ModeNormal;
        }
        if(key == OF_KEY_TAB) {
            mapping.cycleSelection();
        }
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    ofVec2f movePos = mapping.invert(ofVec2f(x,y));
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    ofVec2f dragPos = mapping.invert(ofVec2f(x,y));
    if (currentMode == ModeNormal) {
        if(isDrag) dragDist = ofDist(dragPos.x, dragPos.y, pressPos.x, pressPos.y);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    pressPos = mapping.invert(ofVec2f(x,y));

    if (currentMode == ModeNormal) {
        isDrag = true;
    }
    else if (currentMode == ModeViewMapping) {
        mapping.setSelection(ofVec2f(x,y));
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    ofVec2f releasePos = mapping.invert(ofVec2f(x,y));

    if (currentMode == ModeNormal) {
        isDrag = false;
        cout<<"adding hold"<<endl;
        beta->addHold(pressPos, dragDist);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
    ofSetupScreenPerspective(w,h,60,0,100);

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
