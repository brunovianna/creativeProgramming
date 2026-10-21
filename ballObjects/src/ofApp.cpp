#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myBall =  Ball();
}

//--------------------------------------------------------------
void ofApp::update(){
    myBall.update();

    for (Ball &b : myBalls) {
        b.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //myBall.display();
    int i=0;
    for (Ball b : myBalls) {
        b.display();

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

    Ball b;
    b = Ball(x,y);
    myBalls.push_back(b);

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

Ball::Ball() {
    location = ofVec2f(ofRandom((float)(ofGetWindowWidth()/2)),ofRandom((float)(ofGetWindowHeight()/2)));
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    colour = ofColor (ofRandom(256)); 
    size = 10;
};

Ball::Ball(int _x, int _y) { //same name, different parameters
    location = ofVec2f(_x,_y);
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    colour = ofColor (ofRandom(256)); 
    size = 10;
};


void Ball::display() {
    ofSetColor (colour);
    ofDrawCircle(location.x, location.y, size);
    cout << "speed: " << velocity.x << " " << velocity.y << "\n";
};

void Ball::update() {

    int newX = location.x + velocity.x ;
    if ((newX> 0)&&(newX< ofGetWidth())) {
        location.x = newX;
        cout << "updatex: " << location.x << "\n";
    } else {
        velocity.x = -velocity.x;
        location.x = location.x + velocity.x ;
         
    }

    int newY = location.y + velocity.y ;
    if ((newY> 0)&&(newY< ofGetHeight())) {
        location.y = newY;
    } else {
        velocity.y = -velocity.y;
        location.y = location.y + velocity.y ;
    }

};