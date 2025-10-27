#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myBall =  Ball();
    gravity = ofVec2f (0,3.1f);
    wind = ofVec2f(0.01,0);
    ofSetCircleResolution(100);
}

//--------------------------------------------------------------
void ofApp::update(){
    //myBall.update();

    //int i=0;


    for (Ball &b : myBalls) {
        ofVec2f force = gravity + wind;
        b.applyForce(force);
        b.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //myBall.display();
    if (ofGetMousePressed(1)) {
        wind = ofVec2f (2,0);
    } else {
        wind = ofVec2f (0,0);
    }
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

    if (button==0) {
        Ball b;
        b = Ball(x,y);
        myBalls.push_back(b);
    }    

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
    acceleration = ofVec2f(0,0);
    mass =ofRandom(10,100); 
    colour = ofColor::white;

};

Ball::Ball(int _x, int _y) { //same name, different parameters
    location = ofVec2f(_x,_y);
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    acceleration = ofVec2f(0,0);
    mass = ofRandom(10,100); 
    colour = ofColor(ofRandom(150,255));

};


void Ball::display() {
    ofFill();
    ofSetColor (colour);
    ofDrawCircle(location.x, location.y, mass);
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor (0);
    ofDrawCircle(location.x, location.y, mass);
    
};


void Ball::applyForce(ofVec2f _force) {
    acceleration = _force / mass;
}

void Ball::update() {


    velocity = velocity + acceleration;


    int newX = location.x + velocity.x ;
    if ((newX> 0)&&(newX< ofGetWidth())) {
        location.x = newX;
    } else {
        velocity.x *= -0.8;
        location.x = location.x + velocity.x ;
         
    }

    int newY = location.y + velocity.y ;
    if ((newY > ofGetHeight())) {
        location.y = ofGetHeight();
        velocity.y *= -0.8;
    } else location.y = newY;




};