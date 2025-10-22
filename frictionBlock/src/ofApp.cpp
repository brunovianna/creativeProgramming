#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(240);
    ofSetFrameRate(60);
    ofEnableSmoothing();

    pos.set(ofGetWidth()/2, ofGetHeight() - 60); // starting position
    vel.set(0, 0);
    acc.set(0, 0);
    
    mass = 1.0;
    gravity = 0.5;     // downward acceleration
    friction = 0.05;   // friction coefficient

}

//--------------------------------------------------------------
void ofApp::update(){
    // apply gravity
    acc.y += gravity;

    // apply friction only if on the "ground"
    float groundY = ofGetHeight() - 50;
    if (pos.y >= groundY) {
        pos.y = groundY;
        vel.y = 0;
        acc.y = 0; // reset vertical accel

        if (fabs(vel.x) > 0.001) {
            float frictionForce = -friction * vel.x;
            acc.x += frictionForce;
        } else {
            vel.x = 0;
        }
    }

    // if mouse held, apply force toward mouse
    if (ofGetMousePressed(0)) {
        ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
        ofVec2f dir = mouse - pos;
        float distance = dir.length();
        if (distance > 1.0) {
            dir.normalize();
            ofVec2f force = dir * (distance * 0.01); // scale force
            acc += force / mass;
        }
    }

    vel += acc;
    pos += vel;

    acc.set(0);

    // check boundaries
    if (pos.x>ofGetWidth()) {
        pos.x = ofGetWidth();
    }
    if (pos.x<0) {
        pos.x = 0;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float groundY = ofGetHeight() - 50;
    
    // draw ground
    ofSetColor(100);
    ofDrawRectangle(0, groundY, ofGetWidth(), 50);

    // draw block
    ofSetColor(200, 100, 100);
    float size = 40;
    ofDrawRectangle(pos.x - size/2, pos.y - size/2, size, size);

    // draw force arrow if mouse held
    if (ofGetMousePressed(0)) {
        ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
        ofSetColor(50, 50, 255);
        ofSetLineWidth(3);
        ofDrawLine(pos, mouse);

        ofVec2f dir = (mouse - pos).getNormalized() * 20;
        ofVec2f perp(-dir.y, dir.x);
        ofDrawLine(mouse, mouse - dir + perp * 0.3);
        ofDrawLine(mouse, mouse - dir - perp * 0.3);
    }

}


