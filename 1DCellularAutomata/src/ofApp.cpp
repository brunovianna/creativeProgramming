#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	int rules[8] = { 0, 0, 0, 1, 1, 1, 0, 1 }; 
	// Rule 26:  {0, 1, 0, 1, 1, 0, 0, 0}
	// Rule 30:  {0, 1, 1, 1, 1, 0, 0, 0}
	// Rule 90:  {0, 1, 0, 1, 1, 0, 1, 0}
	// Rule 110: {0, 1, 1, 1, 0, 1, 1, 0}
	// Rule 184: {0, 0, 0, 1, 1, 1, 0, 1}
	ca = CA(3, 0.5, rules); //CA (CellWidth, Randomness, Ruleset)

    //ca.rules(1,0,1);
    // ca.generateCA();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetFrameNum()>5)  ca.nextStep();
}

//--------------------------------------------------------------
void ofApp::draw(){
    //ca.displayAllGenerations();
    ca.displayAllGenerations();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
