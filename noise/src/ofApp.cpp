#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){




    for (float y=0;y<ofGetWidth();y+=1) {
           noiseline.lineTo(y,ofSignedNoise(y*0.01f)*ofGetHeight());
    }
    for (int y=0;y<ofGetWidth();y+=1) {
           randomline.lineTo(y,(ofGetHeight()/2-ofRandomHeight())/2);
    }
 
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    // random and noise lines:

    // ofSetColor(ofColor::orange);
    // ofTranslate(0,ofGetHeight()/2);
    // randomline.draw();
    // ofSetColor(ofColor::magenta);
    // noiseline.draw();
    // ofTranslate(0,-ofGetHeight()/2);

    
    
    // noise rotation squares:

    // float squaresize = 10.0f;
    // float diagonal = sqrt(2*squaresize*squaresize);
    // ofSetColor(ofColor::white);
    // ofNoFill();
    // for (float x= 0; x<ofGetWidth();x+=diagonal) {
    //     ofPushMatrix();
    //     for (float y=0;y<ofGetHeight();y+=diagonal) {
    //         ofPushMatrix();
    //         float ang = 45.0f+180*ofNoise(x*0.001,y*0.001);
    //         cout << ang << "\n";
    //         ofRotateDeg(ang);
    //         ofDrawRectangle(0,0,squaresize,squaresize);
    //         ofPopMatrix();
    //         ofTranslate(0,diagonal);
    //     }
    //     ofPopMatrix();
    //     ofTranslate(diagonal,0);
    // }

    //noise shadings
    
    // for (float x= 0; x<ofGetWidth();x++) {
    //     for (float y=0;y<ofGetHeight();y++) {
    //         ofSetColor(255*ofNoise(x*0.001, y*0.001));
    //         ofDrawCircle(x,y,2);
    //     }
    // }




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
