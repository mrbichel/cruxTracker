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
    
    plane.setResolution(16, 9);
 
}

//--------------------------------------------------------------
void Meshplane::update() {

}




//--------------------------------------------------------------
void Meshplane::draw() {
    
    
    float width     = ofGetWidth();
    float height    = ofGetHeight();
    // Plane
    plane.set( width*1., height*1. );
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0.);
    plane.drawWireframe();
    
    }
