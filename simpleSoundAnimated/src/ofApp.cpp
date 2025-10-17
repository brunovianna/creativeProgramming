#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	beats.load("1085.mp3");

    pointLight.setup();
    pointLight.setPosition(-100, 200,300);
	pointLight.enable();
    ofEnableLighting();
    ofEnableDepthTest();


}

//--------------------------------------------------------------
void ofApp::update(){

	// update the sound playing system:
	ofSoundUpdate();

    float summedBands;
    int numBands = 4;

	float * val = ofSoundGetSpectrum(numBands);		// request 4 values for fft
    summedBands = 0.0f;
	for (int i = 0;i < numBands; i++){
		summedBands += val[i];
	}

    averagedBands = summedBands  / numBands;



        // let the smoothed value sink to zero:
    smoothed *= 0.96f;
    
    // take the max, either the smoothed or the incoming:
    if (smoothed < averagedBands) smoothed = averagedBands;




}

//--------------------------------------------------------------
void ofApp::draw(){


    cam.begin();
    ofSetColor(0,200,0);
    ofTranslate(0,smoothed*200.0f);
    sph.draw();
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
    beats.play();
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
