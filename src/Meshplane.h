//
//  Meshplane.h
//  cruxTracker
//
//  Created by pd on 12/9/13.
//
//
#include "ofmain.h"

class Meshplane
{
public:
    // Initialize the object
    void setup();
    
    // Update the object
    void update();
    
    
    // Draw the mapping selection
    void draw();
    
    ofPlanePrimitive plane;
    ofLight pointLight;
    ofColor lightColor;
    ofVec3f center;
    ofImage texture;
    ofMaterial material;
    vector<ofMeshFace> triangles;
};