#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofTranslate(0, 250);
	ofRotateRad(-1.0f+ofGetMouseX() / 600.0f);
	ofSetLineWidth(8);
	ofDrawLine(0, 0, 200, 0);

	ofTranslate(200, 0);
	ofRotateRad(-1.0f + ofGetMouseX() / 600.0f);
	ofSetLineWidth(4);
	ofDrawLine(0, 0, 200, 0);

	ofTranslate(200, 0);
	ofRotateRad(-1.0f + ofGetMouseX() / 600.0f);
	ofSetLineWidth(2);
	ofDrawLine(0, 0, 200, 0);

	ofTranslate(200, 0);
	ofRotateRad(-1.0f + ofGetMouseX() / 600.0f);
	ofSetLineWidth(1);
	ofDrawLine(0, 0, 200, 0);


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
