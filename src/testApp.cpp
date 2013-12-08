#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    
    beta = new Beta();
    tracker = new Tracker();
    
    beta->setup();
    tracker->setup();

    mapping.setup();
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);

    parameters.setName("GUI Parameters");
    parameters.add(intForSlider.set("Blob threshold", 40, 0, 200));
    parameters.add(intForSlider1.set("Gravity", 40, 0, 200));
    parameters.add(intForSlider2.set("Particles", 40, 0, 200));
    parameters.add(boolForToogle.set("Fullscreen",false));
    gui.setup(parameters);


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
    
    tracker->threshold = intForSlider;
    if (boolForToogle == true){
        ofSetFullscreen(true);
        
    }
        
    else { 
        ofSetFullscreen(false);

    
    }

    tracker->update();
    world.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0, 0, 0);
    
    beta->draw();
    
    
    if(isDrag) {
        ofSetColor(255,40,40,100);
        ofDrawSphere(pressPos, dragDist);
    }
	
    mapping.drawInterface();

    mapping.begin();

    if(debugOn) {
        tracker->debugDraw();
        world.drawDebug();
    
    }

    mapping.end();

    gui.draw();
    ofFill();
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == 'f') {
        debugOn = !debugOn;
        cout<<"Debug mode"<<endl;
    }
    if(key == ' ') {
        tracker->bLearnBakground = true;
        cout<<"addet new background"<<endl;
    }
    if(key == OF_KEY_ESC) {
        fullscreen = true;
        cout<<"Fullscreen"<<endl;
    }
    if(key == OF_KEY_F10) {
        mapping.toggleInterface();
    }
    if(key == OF_KEY_TAB) {
        mapping.cycleSelection();
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
    
    // isDrag = true;
    
    pressPos = ofVec2f(x,y);
    
    mapping.setSelection(pressPos);
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
