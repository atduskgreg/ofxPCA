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
    ofxPCAResult();
    ofxPCAResult(vector<ofVec3f> eVectors, vector<float> eValues);
    ~ofxPCAResult();
    vector<ofVec3f> eigenvectors;
    vector<float> eigenvalues;
};

typedef Matrix<float, Dynamic, Dynamic, RowMajor> MatrixVec3f;


class ofxPCA{
public:
    ofxPCA();
    ~ofxPCA();
    

    ofxPCAResult analyze(const vector<ofVec3f>& points);
    void loadData(const vector<ofVec3f>& points);
    // perform analysis on subset of existing matrix of data loaded using loadData
    ofxPCAResult analyze(int startCol, int startRow, int numCols, int numRows);
    

private:
    MatrixVec3f data;    
};