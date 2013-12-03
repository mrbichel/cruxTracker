//
//  Beta.h
//  cruxTracker
//
//  Created by Johan Bichel Lindegaard on 02/12/2013.
//
//

#pragma once


struct Hold {
    ofVec3f pos;
    float radius=4;
};

struct Route {
    vector<Hold*> holds;
};

// a wall is a mesh
struct Wall {
    ofMesh mesh;
};


class Beta {

public:
    
    Route * route;
    
    Wall wall;
    void setup() {
        
        route = new Route();
        
    };
    
    void update() {
        
    };
    
    void draw() {
        
        for(int i=0; i<route->holds.size(); i++) {
            
            ofColor(255);
            ofDrawSphere(route->holds[i]->pos,route->holds[i]->radius);
            
            if(i != 0) {
                ofLine(route->holds[i]->pos, route->holds[i-1]->pos);
            }
            
        }
        
    };
    
    void addHold(ofVec3f pos, float radius) {
        
        Hold * hold;
        hold = new Hold();
        
        hold->pos = pos;
        hold->radius = radius;
        
        route->holds.push_back(hold);
        
    };
    
    
    void debugDraw() {
    };
    
};