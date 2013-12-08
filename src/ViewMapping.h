#pragma once

#include "ofMain.h"

class ViewMapping
    {
public:
    // Initialize the object
    void setup();

    // Draw the mapping selection
    void drawInterface();

    // Select the next point of the mapping quad
    void cycleSelection();

    // Set the selected mapping quad to the given position (in window
    // coordinates)
    void setSelection(const ofVec2f& x);

    // Add a mapping matrix to the openframeworks matrix stack.
    void begin();

    // Restore the openframeworks matrix stack to the state before calling
    // begin.
    void end();

    // Transform a point from window coordinates to render plane
    // coordinates. Use for mouse coordinates for example
    ofVec2f invert(const ofVec2f& p);

private:
    void drawLine(const ofVec2f& a, const ofVec2f& b);

    void updateMatrices();
    void gaussianElimination(float *input, int n);
    ofMatrix4x4 homography(const ofVec2f* src, const ofVec2f* dst);

    ofVec2f quad[4];
    ofMatrix4x4 mapping;
    ofMatrix4x4 inverse;

    int currentSelection;
    };

