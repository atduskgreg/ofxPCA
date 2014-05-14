//
//  ofxPCA.h
//  emptyExample
//
//  Created by Greg Borenstein on 5/12/14.
//
//
#pragma once

#include "../libs/Eigen/include/Eigen/Core"
#include "../libs/Eigen/include/Eigen/Eigen"
#include "ofMain.h"

using namespace Eigen;

class ofxPCAResult{
public:
    ofxPCAResult(vector<ofVec3f> eVectors, vector<float> eValues);
    ~ofxPCAResult();
    vector<ofVec3f> eigenvectors;
    vector<float> eigenvalues;
};


class ofxPCA{
public:
    ofxPCA();
    ~ofxPCA();

    ofxPCAResult analyze(vector<ofVec3f>& points);
};