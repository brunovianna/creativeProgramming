#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(30); // Dark background
    ofEnableDepthTest(); // Crucial for 3D
    ofEnableAntiAliasing();
    ofEnableSmoothing();

    pointLight.setup();
    pointLight.setPosition(-100, 200,300);
	pointLight.enable();
    ofEnableLighting();

    // 1. Set up the mesh
    mesh.clear();
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // 2. Create initial points as vec3 with random Z
    glm::vec3 p1(500, 0, ofRandom(-20, 20));
    glm::vec3 p2(1000, 1000, ofRandom(-20, 20));
    glm::vec3 p3(0, 1000, ofRandom(-20, 20));

    // 3. Start the recursive mesh-building process
    splitAndAdd(Triangle(p1, p2, p3));
    mesh.setupIndicesAuto(); // This also calculates flat normals
}

//--------------------------------------------------------------
void ofApp::update(){
    // No update logic needed
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 1. Begin 3D camera view
    cam.begin();

    // 2. Center the drawing (since points are around 500, 500)
    // This moves the mesh's center to (0, 0) before rotation
    ofTranslate(-ofGetWidth()/2, -ofGetHeight()/2,-500);

    // 3. Draw the single, complete mesh
    // ofPushMatrix();
    // ofTranslate(0, ofGetHeight()/2);

    mesh.draw();
    ofSetColor(0);
    mesh.drawWireframe();
    // ofPopMatrix();

    // ofPushMatrix();
    // ofRotateYDeg(240);
    // ofTranslate(-ofGetWidth(), 0);
    // mesh.draw();
    // ofPopMatrix();

    // ofPushMatrix();
    // ofTranslate(ofGetWidth(), 0);
    // ofRotateYDeg(120);
    // mesh.draw();
    // ofPopMatrix();


    // Optional: Draw the wireframe on top to see the triangles


    cam.end();
}

// Renamed from splitAndDraw to splitAndAdd
void ofApp::splitAndAdd(Triangle _t) {

    // --- Vertex and Area Setup ---
    vector <int> els = {0, 1, 2};
    int lefOutIndex = ofRandom(3);
    
    // Points are now glm::vec3
    glm::vec3 leftOut = _t.points[lefOutIndex];
    els.erase(els.begin() + lefOutIndex);
    glm::vec3 p1 = _t.points[els[0]];
    glm::vec3 p2 = _t.points[els[1]];

    float a = _t.area();
    
    // --- This block replaces your ofPath ---
    // 1. Add the 3 vertices of this triangle to the mesh
    mesh.addVertex(p1);
    mesh.addVertex(p2);
    mesh.addVertex(leftOut);

    // 2. Add colors (using the corrected map from our previous discussion)
    // This maps large areas (500k) to white and small areas (10k) to black
    float gray = 20+ofNoise(counter*0.05)*200;
    ofColor triColor(gray);

    mesh.addColor(triColor);
    mesh.addColor(triColor);
    mesh.addColor(triColor);
    // --- End of mesh-adding block ---

    cout << counter++ << " " << a << "\n";

    // --- Recursion ---
    if (a > 10000) {
        
        // 1. Find the 3D difference vector
        glm::vec3 diff = p2 - p1;

        // 2. Create new 3D points by interpolating X, Y, and Z
        // This creates a continuous, albeit jagged, surface.
        glm::vec3 point1 = p1 + diff * 0.33;
        glm::vec3 point2 = p1 + diff * 0.66;
        
        // 3. (Optional) Add fractal displacement
        // To make it more "random" like a terrain, add a new, smaller
        // random offset to the Z of the new points.
        // float z_offset_scale = ofMap(a, 500000, 10000, 150, 0);
        float z_offset_scale = 20+ofNoise(counter*0.05)*100;
        point1.z += ofRandom(0, z_offset_scale);
        point2.z += ofRandom(0, z_offset_scale);

        // 4. Recurse using the new 3D points
        splitAndAdd(Triangle(point1, p1, leftOut));
        splitAndAdd(Triangle(point1, point2, leftOut));
        splitAndAdd(Triangle(point2, p2, leftOut));
    }
}


//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}