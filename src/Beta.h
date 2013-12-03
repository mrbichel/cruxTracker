//
//  Beta.h
//  cruxTracker
//
//  Created by Johan Bichel Lindegaard on 02/12/2013.
//
//

#pragma once


struct Hold {
    ofVec2f pos;
};


struct Route {
    vector<Hold> holds;
};


// a wall is a mesh
struct Wall {
    ofMesh mesh;
};


class Beta {

public:
    Wall wall;
    void setup() {
        
    };
    
};