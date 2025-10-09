#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	for (int i = 0; i < 300; i++) {
		posX[i] = ofRandom(ofGetWidth());
		posY[i] = ofRandom(ofGetHeight());
		velX[i] = ofRandom(-2, 2);
		velY[i] = ofRandom(-2, 2);
		diameter[i] = ofRandom(10, 30);
		gray[i] = ofRandom(100, 200);

	}



	ofSetBackgroundAuto(true);
	ofBackground(255, 1); //alpha from 0 to 255
	ofSetFrameRate(60);
	ofSetColor(0);
}

//--------------------------------------------------------------
void ofApp::update() {


	for (int i = 0; i < 300; i++)
	{
		posX[i] = posX[i] + velX[i];
		posY[i] = posY[i] + velY[i];

		if (posY[i] > ofGetHeight() || posY[i] < 0) {
			velY[i] = -velY[i];
		}

		if (posX[i] > ofGetWidth() || posX[i] < 0) {
			velX[i] = -velX[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {


	for (int i = 0; i < 300; i++) {
		ofSetColor(gray[i]);
		ofDrawCircle(posX[i], posY[i], diameter[i]);
		//ofNoFill();
	}




	/*
	*
	*
	ofBeginShape();
	ofCurveVertex(400, 135);
	ofCurveVertex(215, 135);
	ofCurveVertex(365, 25);
	ofCurveVertex(305, 200);
	ofCurveVertex(250, 25);
	ofEndShape();

	int maxRadius = 100;
	int radiusStepSize = 5;
	int alpha = 2;
	// draw smaller and smaller circles and layering (increasing) opaqueness
	for (int radius = maxRadius; radius > 0; radius -= radiusStepSize) {
		ofSetColor(0, alpha);
		ofDrawCircle(ofGetMouseX(), ofGetMouseY(), radius);
	}
	*/


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
