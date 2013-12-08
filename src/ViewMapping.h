#pragma once

#include <vector>

#include "ofMain.h"

class ViewMapping {
    public:
        void setup();
        void drawInterface();

        void cycleSelection();
        void setSelection(const ofVec2f& x);

        void begin();
        void end();

    private:
        void drawLine(const ofVec2f& a, const ofVec2f& b);

        void gaussianElimination(float *input, int n);
        void updateMatrix();

        std::vector<ofVec2f> quad;
        ofMatrix4x4 transform;

        int currentSelection;

};

