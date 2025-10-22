#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    planet = Planet(ofGetWidth()/2, ofGetHeight()/2);

    //start with a well -behaved moon
    Moon m = Moon(ofVec2f(ofGetWidth()/2,ofGetHeight()/4),ofVec2f(1,0));
    myMoons.push_back(m);

}

//--------------------------------------------------------------
void ofApp::update(){
    for (Moon &m : myMoons) {
        //b.applyForce(gravity);
        planet.attract(m);
        m.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    planet.display();
    for (Moon m : myMoons) {
        m.display();

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
        Moon m;
        m = Moon(x,y);
        myMoons.push_back(m);
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

Moon::Moon() {
    location = ofVec2f(ofRandom((float)(ofGetWindowWidth()/2)),ofRandom((float)(ofGetWindowHeight()/2)));
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    acceleration = ofVec2f(0,0);
    mass =ofRandom(10,100); 
    colour = ofColor::white;

};

Moon::Moon(int _x, int _y) { //same name, different parameters
    location = ofVec2f(_x,_y);
    velocity = ofVec2f(ofRandom(-1,1),ofRandom(-1,1));
    acceleration = ofVec2f(0,0);
    mass = ofRandom(10,100); 
    colour = ofColor(ofRandom(150,255));

};

Moon::Moon(ofVec2f _location, ofVec2f _velocity ) { //same name, different parameters
    location = _location;
    velocity = _velocity;
    acceleration = ofVec2f(0,0);
    mass = 50; 
    colour = ofColor::yellow;

};


void Moon::display() {
    ofFill();
    ofSetColor (colour);
    ofDrawCircle(location.x, location.y, mass);
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor (0);
    ofDrawCircle(location.x, location.y, mass);
    
};


void Moon::applyForce(ofVec2f _force) {
    acceleration = _force / mass + acceleration;
}

void Moon::update() {


    velocity = velocity + acceleration;
    location = location + velocity;

    // int newX = location.x + velocity.x ;
    // if ((newX> 0)&&(newX< ofGetWidth())) {
    //     location.x = newX;
    // } else {
    //     velocity.x = -velocity.x;
    //     location.x = location.x + velocity.x ;
         
    // }

    // int newY = location.y + velocity.y ;
    // if ((newY > ofGetHeight())) {
    //     location.y = ofGetHeight();
    //     velocity.y *= -1;
    // } else location.y = newY;

    acceleration.set(0,0);
};


Planet::Planet() {
    location = ofVec2f(ofRandom((float)(ofGetWindowWidth()/2)),ofRandom((float)(ofGetWindowHeight()/2)));
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    mass =ofRandom(10,100); 
    colour = ofColor::white;

};

Planet::Planet(int _x, int _y) { //same name, different parameters
    location = ofVec2f(_x,_y);
    velocity = ofVec2f(0,0);
    mass = 200; 
    colour = ofColor::brown;

};


void Planet::display() {
    ofFill();
    ofSetColor (colour);
    ofDrawCircle(location.x, location.y, 100);
    ofNoFill();
    ofSetLineWidth(5);
    ofSetColor (0);
    ofDrawCircle(location.x, location.y, 100);
    
};


void Planet::attract(Moon& _moon) {
    ofVec2f force = - _moon.location + location; // getting the direction
    float distance = force.length(); //getting the distance

    float gravity = 0.006;

    float strength = gravity * (_moon.mass * mass) / (distance * distance);
    force = force * strength;
    _moon.applyForce(force);
}

void Planet::update() {



};