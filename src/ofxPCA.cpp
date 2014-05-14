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

ofxPCAResult ofxPCA::analyze(vector<ofVec3f>& points){
    int rows = points.size();
    int cols = 3; // vec3f has three components

    // custom Matrix type for loading in data from ofVec3fs
    typedef Matrix<float, Dynamic, Dynamic, RowMajor> MatrixVec3f;

    // vector's data() member function returns a pointer to the first element
    // the elements are laid out continuously in memory cf http://www.frogatto.com/?p=26
    // casting that to a pointer to a float will treat the vector as a 1D array of floats
    Map<MatrixVec3f> data((float *)points.data(), rows, cols);
    
    MatrixVec3f meanCentered = data.rowwise() - data.colwise().mean();
    MatrixVec3f cov = (meanCentered.adjoint() * meanCentered) / double(data.rows());
    EigenSolver<MatrixVec3f> eig(cov);
    
    vector<pair<float,int> > pi;
    for (int i = 0 ; i < cols; i++){
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



ofxPCAResult::ofxPCAResult(vector<ofVec3f> eVectors, vector<float> eValues){
    eigenvectors = eVectors;
    eigenvalues = eValues;
}

ofxPCAResult::~ofxPCAResult(){
}