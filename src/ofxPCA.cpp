//
//  ofxPCA.cpp
//  emptyExample
//
//  Created by Greg Borenstein on 5/12/14.
//
//

#include "ofxPCA.h"

ofxPCA::ofxPCA(){
}

ofxPCA::~ofxPCA(){
}

void ofxPCA::loadData(const vector<ofVec3f>& points){
    int n = 3; // vec3f has three components
    data = Map<MatrixVec3f>((float *)points.data(), points.size(), n);
}

ofxPCAResult ofxPCA::analyze(int startCol, int startRow, int numCols, int numRows){
    MatrixVec3f d = data.block(startRow, startCol, numRows, numCols);
    
    
    MatrixVec3f meanCentered = d.rowwise() - d.colwise().mean();
    MatrixVec3f cov = (meanCentered.adjoint() * meanCentered) / double(d.rows());
    EigenSolver<MatrixVec3f> eig(cov);
    
    vector<pair<float,int> > pi;
    for (int i = 0 ; i < d.cols() ; i++){
        pi.push_back(make_pair(eig.eigenvalues().real()[i], i));
    }

    // sort eigenvalues into descending order
    sort(pi.rbegin(), pi.rend());
    
    // put them into the ofxPCAResult object
    vector<ofVec3f> rEigenvectors;
    vector<float> rEigenvalues;
    for(auto iterator = pi.begin(); iterator != pi.end(); ++iterator){
        pair<float,int> ev = *iterator;
        rEigenvalues.push_back(ev.first);
        VectorXf v = eig.eigenvectors().real().row(ev.second);
        rEigenvectors.push_back(ofVec3f(v[0], v[1], v[2]));
    }
    
    return ofxPCAResult(rEigenvectors, rEigenvalues);
}


ofxPCAResult ofxPCA::analyze(const vector<ofVec3f>& points){
    loadData(points);
    return analyze(0,0,3, points.size());
}

ofxPCAResult::ofxPCAResult(){
}


ofxPCAResult::ofxPCAResult(vector<ofVec3f> eVectors, vector<float> eValues){
    eigenvectors = eVectors;
    eigenvalues = eValues;
}



ofxPCAResult::~ofxPCAResult(){
}