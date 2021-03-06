#include "ViewMapping.h"

//--------------------------------------------------------------
void ViewMapping::setup()
    {
    // initialize the mapping quad to the identity mapping
    quad[0] = ofVec2f(0.0, 0.0);
    quad[1] = ofVec2f(ofGetWindowWidth(), 0.0);
    quad[2] = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
    quad[3] = ofVec2f(0.0, ofGetWindowHeight());
    updateMatrices();

    currentSelection = 0;
    }

//--------------------------------------------------------------
void ViewMapping::cycleSelection()
    {
    currentSelection = (currentSelection + 1) % 4;
    }

//--------------------------------------------------------------
void ViewMapping::setSelection(const ofVec2f& x)
    {
    quad[currentSelection] = x;
    updateMatrices();
    }

//--------------------------------------------------------------
void ViewMapping::drawInterface()
    {
    ofBackground(255, 255, 255);

    ofSetColor(0, 0, 0, 255);
    ofNoFill();

    // draw mapping quad
    drawLine(quad[0], quad[1]);
    drawLine(quad[1], quad[2]);
    drawLine(quad[2], quad[3]);
    drawLine(quad[3], quad[0]);

    // draw selected point
    ofVec2f& current = quad[currentSelection];
    ofCircle(current.x, current.y, 10);
    }

//--------------------------------------------------------------
void ViewMapping::begin()
    {
    ofPushMatrix();
    ofMultMatrix(mapping);
    }

//--------------------------------------------------------------
void ViewMapping::end()
    {
    ofPopMatrix();
    }

//--------------------------------------------------------------
ofVec2f ViewMapping::invert(const ofVec2f& p)
    {
    // do the inverse mapping
    ofVec4f result = inverse * ofVec4f(p.x, p.y, 0.0, 1.0);

    // scale by w to go from homogenous coordinates
    return ofVec2f(result.x/result.w, result.y/result.w);
    }

//--------------------------------------------------------------
void ViewMapping::drawLine(const ofVec2f& a, const ofVec2f& b)
    {
    ofLine(a.x, a.y, b.x, b.y);
    }

//--------------------------------------------------------------
void ViewMapping::updateMatrices()
    {
    ofVec2f winquad[4];
    winquad[0] = ofVec2f(0.0, 0.0);
    winquad[1] = ofVec2f(ofGetWindowWidth(), 0.0);
    winquad[2] = ofVec2f(ofGetWindowWidth(), ofGetWindowHeight());
    winquad[3] = ofVec2f(0.0, ofGetWindowHeight());

    mapping = homography(winquad, quad);
    inverse = ofMatrix4x4::getTransposedOf(homography(quad, winquad));
    }

//--------------------------------------------------------------

// NOTE: the two functions below are adapted from code from this
// github repository: github.com/hvfrancesco/ProjectionMapping.
// They are licensed under GPL but are both pretty much adaptions
// from other sources (wikipedia/hartley & zisserman). What are
// the implications of this?

void ViewMapping::gaussianElimination(float *input, int n)
    {
    // ported to c from pseudocode in
    // http://en.wikipedia.org/wiki/Gaussian_elimination

    float * A = input;
    int i = 0;
    int j = 0;
    int m = n-1;
    while (i < m && j < n)
        {
        // Find pivot in column j, starting in row i:
        int maxi = i;
        for(int k = i+1; k<m; k++)
            {
            if(fabs(A[k*n+j]) > fabs(A[maxi*n+j]))
                {
                maxi = k;
                }
            }
        if (A[maxi*n+j] != 0)
            {
            // swap rows i and maxi, but do not change the value of i
            if(i!=maxi)
                {
                for(int k=0; k<n; k++)
                    {
                    float aux = A[i*n+k];
                    A[i*n+k]=A[maxi*n+k];
                    A[maxi*n+k]=aux;
                    }
                }
            // Now A[i,j] will contain the old value of A[maxi,j].
            // divide each entry in row i by A[i,j]
            float A_ij=A[i*n+j];
            for(int k=0; k<n; k++)
                {
                A[i*n+k]/=A_ij;
                }
            // Now A[i,j] will have the value 1.
            for(int u = i+1; u< m; u++)
                {
                // subtract A[u,j] * row i from row u
                float A_uj = A[u*n+j];
                for(int k=0; k<n; k++)
                    {
                    A[u*n+k]-=A_uj*A[i*n+k];
                    }
                // Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
                }
            i++;
            }
        j++;
        }

    //back substitution
    for(int i=m-2; i>=0; i--)
        {
        for(int j=i+1; j<n-1; j++)
            {
                A[i*n+m]-=A[i*n+j]*A[j*n+m];
                //A[i*n+j]=0;
            }
        }
    }

//--------------------------------------------------------------
ofMatrix4x4 ViewMapping::homography(const ofVec2f* src, const ofVec2f* dst)
    {
    // create the equation system to be solved
    //
    // from: Multiple View Geometry in Computer Vision 2ed
    //       Hartley R. and Zisserman A.
    //
    // x' = xH
    // where H is the homography: a 3 by 3 matrix
    // that transformed to inhomogeneous coordinates for each point
    // gives the following equations for each point:
    //
    // x' * (h31*x + h32*y + h33) = h11*x + h12*y + h13
    // y' * (h31*x + h32*y + h33) = h21*x + h22*y + h23
    //
    // as the homography is scale independent we can let h33 be 1 (indeed any of the terms)
    // so for 4 points we have 8 equations for 8 terms to solve: h11 - h32
    // after ordering the terms it gives the following matrix
    // that can be solved with gaussian elimination:

    float p[8][9]=
        {
        {-src[0].x, -src[0].y, -1,   0,   0,  0, src[0].x*dst[0].x, src[0].y*dst[0].x, -dst[0].x }, // h11
        {  0,   0,  0, -src[0].x, -src[0].y, -1, src[0].x*dst[0].y, src[0].y*dst[0].y, -dst[0].y }, // h12

        {-src[1].x, -src[1].y, -1,   0,   0,  0, src[1].x*dst[1].x, src[1].y*dst[1].x, -dst[1].x }, // h13
        {  0,   0,  0, -src[1].x, -src[1].y, -1, src[1].x*dst[1].y, src[1].y*dst[1].y, -dst[1].y }, // h21

        {-src[2].x, -src[2].y, -1,   0,   0,  0, src[2].x*dst[2].x, src[2].y*dst[2].x, -dst[2].x }, // h22
        {  0,   0,  0, -src[2].x, -src[2].y, -1, src[2].x*dst[2].y, src[2].y*dst[2].y, -dst[2].y }, // h23

        {-src[3].x, -src[3].y, -1,   0,   0,  0, src[3].x*dst[3].x, src[3].y*dst[3].x, -dst[3].x }, // h31
        {  0,   0,  0, -src[3].x, -src[3].y, -1, src[3].x*dst[3].y, src[3].y*dst[3].y, -dst[3].y }, // h32
        };

    gaussianElimination(&p[0][0],9);

    // gaussian elimination gives the results of the equation system
    // in the last column of the original matrix.
    // opengl needs the transposed 4x4 matrix:
    return ofMatrix4x4(
        p[0][8], p[3][8], 0, p[6][8],
        p[1][8], p[4][8], 0, p[7][8],
        0,       0,       0, 0,
        p[2][8], p[5][8], 0, 1);
    }

