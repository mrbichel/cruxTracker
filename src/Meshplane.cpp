//
//  Meshplane.ccp
//  cruxTracker
//
//  Created by pd on 12/9/13.
//
//
#include "Meshplane.h"


//--------------------------------------------------------------
void  Meshplane::setup(){
    
    plane.setResolution(18, 18);
    //plane.resizeToTexture( texture.getTextureReference() );
    
    // turn on smooth lighting //
    //ofSetSmoothLighting(true);
    
    // Point lights emit light in all directions //
    // set the diffuse color, color reflected from the light source //
    //pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
    
    // specular color, the highlight/shininess color //
	//pointLight.setSpecularColor( ofColor(255.f, 200.f, 255.f));
    //pointLight.setPosition(center.x, center.y, 0);
    

    
    
    
}

//--------------------------------------------------------------
void Meshplane::update() {
    //pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
    
    
    
}




//--------------------------------------------------------------
void Meshplane::draw() {
    
    float spinX = sin(ofGetElapsedTimef()/.35f);
    float spinY = cos(ofGetElapsedTimef()/.075f);
    float width     = ofGetWidth();
    float height    = ofGetHeight();
    // Plane
    plane.set( width*1., height*1. );
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0.);
    plane.rotate(spinX, 0.1, 0.0, 0.0);
    plane.rotate(spinY, 0, 0.1, 0.0);
    //ofEnableLighting();
    //pointLight.enable();
    //ofDisableDepthTest();
   
    
    ofSetColor(180);
    ofFill();
    
        
    ofSetColor(200);
    
    //plane.drawWireframe();
    //ofDrawGrid(plane.getPosition().x-0, plane.getPosition().y + 120, 140, 200);
    //plane.draw();
    plane.drawWireframe();
    //ofDisableLighting();
    
    //ofDisableDepthTest();
    
    //plane.drawAxes(plane.getPosition().x-0);
        
    //ofNoFill();

    
    
}
