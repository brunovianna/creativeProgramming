#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetColor (255);
    ofSetLineWidth(2);
    int w = ofGetWidth() ;
    int h = ofGetHeight();
    fbo.allocate (w,h, GL_RGBA);
    fbo.begin();
    int	tInicial=50;
    int randomness = 100;
    int x = tInicial;
	// while (x<500) {
	// 	int y=tInicial;
	// 	while (y<500) {
	// 		ofDrawLine (x+tInicial-ofRandom(randomness),y+tInicial-ofRandom(randomness),x+tInicial-ofRandom(randomness),y+tInicial-ofRandom(randomness));
	// 		y+=50;
	// 	}
	// 	x+=50;
	// }

    for (int i=0;i<10;i++) {
        ofPushMatrix();
        for (int j=0;j<10;j++) {
            ofTranslate(tInicial,0);
            ofPushMatrix();
            ofRotate(ofRandom(180));
            ofScale(ofRandom(0.5,1.5));
            ofDrawLine (0,-50,0,50);
            ofPopMatrix();
        }
        ofPopMatrix();
        ofTranslate(0,tInicial);
    }



    fbo.end();


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    fbo.draw(0,0);
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
