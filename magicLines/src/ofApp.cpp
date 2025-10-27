#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(24);
	ofSetColor(255,6);
	ofBackground(0);
    ofSetBackgroundAuto(false);
	for (int i = 0; i < totalAmount; i++) {
		bodies.push_back(Ball());
	}

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	mx += 0.3 * (ofGetMouseX() - mx);
	my += 0.3 * (ofGetMouseY() - my);
	for (int i = 0; i < totalAmount; i++) bodies[i].render(mx,my);
    ofSetColor(0,150);
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());

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

Ball::Ball () {

    sizeThreshold = 5.0f;
    x = ofRandomWidth();
    y = ofRandomHeight();
    w = ofRandom(1 / sizeThreshold, sizeThreshold);
    xv = 0;
    yv = 0;
    px = x;
    py = y;
    decelerationFactor  = 1.05;
    drag = 0.01;


}

void Ball::render(float _mx,float _my) {
    	if (!ofGetMousePressed()) {
			xv /= decelerationFactor;
			yv /= decelerationFactor;
		}

		xv += drag * (_mx - x) * w;
		yv += drag * (_my - y) * w;

		x += xv;
		y += yv;

        ofSetColor(ofColor::white);
		ofDrawLine(x, y, px, py);
        // ofSetColor(ofColor::red);
        // ofDrawCircle(x,y,3);
		px = x;;
		py = y;
}