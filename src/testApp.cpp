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
    parameters.add(intForSlider2.set("Fov", 60, 20, 120));
    gui.setup(parameters);
    gui.loadFromFile("settings.xml");

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
    
    tracker->threshold = intForSlider;
    debugOn = boolForToogle1;
    
    if (currentMode == ModeNormal) {
        if (boolForToogle == true){
            ofSetFullscreen(true);
        }
            
        else { 
            ofSetFullscreen(false);
        }
        
        meshplane.update();
        tracker->update();
        world.update();
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
        
        camera.begin();
        
        //glEnable( GL_DEPTH_TEST );
        
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
        
        //glDisable( GL_DEPTH_TEST );

        beta->draw();
        
        
        mapping.end();

        if(debugOn) {
            tracker->debugDraw();
            world.drawDebug();
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
