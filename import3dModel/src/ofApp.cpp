#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    pointLight.setup();
    pointLight.setPosition(-100, 200,300);
	pointLight.enable();
    ofEnableLighting();
    ofEnableDepthTest();


    ofEnableDepthTest();

    capiModel.load("BabyCapybara.fbx");
    body = capiModel.getMesh(0);
    eyes = capiModel.getMesh(1);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
    //draw the whole model
    ofRotate (180,1,0,0);
	capiModel.drawFaces();
	capiModel.drawVertices();
	capiModel.drawFaces();
    capiModel.drawWireframe();
   
   
    //draw each mesh
    // ofRotate (180,0,1,0);
    // ofScale(50, 50, 50); // flip the y axis and zoom in a bit
    // eyes.drawWireframe();
    // body.drawWireframe();
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
