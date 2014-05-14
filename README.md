## ofxPCA

An OpenFrameworks addon that implements the Principal Component Analysis dimensionality reduction technique. This technique is useful for finding the axes that explain the most variation in data. This can be used for finding the orientation of a set of points or the normal to a cluster of unoriented points.

This library uses the [Eigen](http://eigen.tuxfamily.org/) linear algebra library for its matrix routines.

### Usage

    // Make a vector of ofVec3fs that you want to do PCA on,
    // for example the vertices of an ofMesh:
    ofxPCAResult result = pca.analyze(mesh.getVertices());
    // The ofxPCAResult object gives you the eigenvectors and
    // eigenvalues sorted in descending order of the eigenvalues,
    // i.e. by the most principal component to the least:
    cout << "top eigenvalue: " << result.eigenvalues[0] << endl;
    ofVec3f ev1 = result.eigenvectors[0]
    cout << "top eigenvector: " <<  ev1.x << "m" << ev1.y << "," << ev1.z << endl;

### Protip

If you get weird compilation errors after importing this addon, make sure that inside of ofxPCA/libs/Eigen/include/Eigen the src/ folder is not included in XCode as a compilation target. If that folder appears in your XCode project, delete it (but make sure to select Remove References rather than Move to Trash). We need those files to exist, but we don't want XCode to try to compile them.