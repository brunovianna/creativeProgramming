#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    img.load("guggenheim.jpg");
    depth.load("depth.png");


    mesh.setMode(OF_PRIMITIVE_POINTS); // we're going to load a ton of points into an ofMesh

    glEnable(GL_POINT_SMOOTH); // use circular points instead of square points
    glPointSize(3); // make the points bigger

	// loop through the image in the x and y axes
    int skip = 4; // load a subset of the points
    for(int y = 0; y < depth.getHeight(); y += skip) {
        for(int x = 0; x < depth.getWidth(); x += skip) {
            ofColor dColor = depth.getColor(x, y);
            //depth is graywscale, so r = g = b
            float z = ofMap(dColor.r, 0, 255, -300, 300);
            
            //mesh.addColor(ofColor::white);
            ofColor iColor = img.getColor(x, y);
            mesh.addColor(iColor);
            
            glm::vec3 pos(x, y, z);
            mesh.addVertex(pos);
        }
    }
    //mesh.setupIndicesAuto();

    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofScale(2, -2, 2); // flip the y axis and zoom in a bit
	ofTranslate(-img.getWidth() / 2, -img.getHeight() / 2);
	mesh.draw();
	cam.end();
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
