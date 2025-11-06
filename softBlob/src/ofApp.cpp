#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetCircleResolution(32);
    ofBackground(20);
    
    seekStrength = 0.15f;
    blobRadius = 80.0f;
    
    // Create blob in center of screen
    createBlob(ofVec2f(ofGetWidth()/2, ofGetHeight()/2), blobRadius, 20);
    
    // Set initial target
    target.set(ofGetWidth() - 100, ofGetHeight()/2);
}

void ofApp::createBlob(ofVec2f center, float radius, int numParticles) {
    particles.clear();
    springs.clear();
    
    // Create particles in a circle
    for (int i = 0; i < numParticles; i++) {
        float angle = ofMap(i, 0, numParticles, 0, TWO_PI);
        Particle p;
        p.pos.x = center.x + cos(angle) * radius * ofRandom(0.7,1.3);
        p.pos.y = center.y + sin(angle) * radius * ofRandom(0.7,1.3);
        p.mass = 1.0f;
        particles.push_back(p);
    }
    
    // Add a center particle
    Particle centerP;
    centerP.pos = center;
    centerP.mass = 2.0f;
    particles.push_back(centerP);
    int centerIdx = particles.size() - 1;
    
    // Connect outer particles to neighbors (ring)
    for (int i = 0; i < numParticles; i++) {
        int next = (i + 1) % numParticles;
        float dist = particles[i].pos.distance(particles[next].pos);
        springs.push_back(Spring(i, next, dist, 0.3f));
    }
    
    // Connect outer particles to center (spokes)
    for (int i = 0; i < numParticles; i++) {
        float dist = particles[i].pos.distance(particles[centerIdx].pos);
        springs.push_back(Spring(i, centerIdx, dist, 0.25f));
    }
    
    // Connect outer particles to opposite side (cross springs for stability)
    for (int i = 0; i < numParticles; i++) {
        int opposite = (i + numParticles/2) % numParticles;
        float dist = particles[i].pos.distance(particles[opposite].pos);
        springs.push_back(Spring(i, opposite, dist, 0.1f));
    }
}

void ofApp::applySpringForces() {
    for (auto& spring : springs) {
        Particle& p1 = particles[spring.i];
        Particle& p2 = particles[spring.j];
        
        ofVec2f diff = p2.pos - p1.pos;
        float dist = diff.length();
        
        if (dist > 0) {
            float force = (dist - spring.restLength) * spring.stiffness;
            ofVec2f forceVec = diff.getNormalized() * force;
            
            p1.applyForce(forceVec);
            p2.applyForce(-forceVec);
        }
    }
}

void ofApp::seekTarget() {
    // Calculate center of mass
    ofVec2f centerOfMass(0, 0);
    float totalMass = 0;
    
    for (auto& p : particles) {
        centerOfMass += p.pos * p.mass;
        totalMass += p.mass;
    }
    centerOfMass /= totalMass;
    
    // Apply seeking force to all particles
    ofVec2f toTarget = target - centerOfMass;
    float dist = toTarget.length();
    
    if (dist > 5) {
        ofVec2f seekForce = toTarget.getNormalized() * seekStrength;
        
        for (auto& p : particles) {
            p.applyForce(seekForce);
        }
    }
}

void ofApp::constrainToScreen() {
    float bounce = 0.8f;
    
    for (auto& p : particles) {
        if (p.pos.x < 0) {
            p.pos.x = 0;
            p.vel.x *= -bounce;
        }
        if (p.pos.x > ofGetWidth()) {
            p.pos.x = ofGetWidth();
            p.vel.x *= -bounce;
        }
        if (p.pos.y < 0) {
            p.pos.y = 0;
            p.vel.y *= -bounce;
        }
        if (p.pos.y > ofGetHeight()) {
            p.pos.y = ofGetHeight();
            p.vel.y *= -bounce;
        }
    }
}

void ofApp::update() {
    // Physics iterations for stability
    int iterations = 3;
    
    for (int iter = 0; iter < iterations; iter++) {
        seekTarget();
        applySpringForces();
        
        for (auto& p : particles) {
            p.update(0.98f);
        }
        
        constrainToScreen();
    }
}

void ofApp::draw() {
    // Draw springs
    ofSetColor(60, 120, 200, 100);
    for (auto& spring : springs) {
        ofDrawLine(particles[spring.i].pos, particles[spring.j].pos);
    }
    
    // Draw particles
    // ofSetColor(100, 200, 255);
    // for (auto& p : particles) {
    //     ofDrawCircle(p.pos, 6);
    // }
    
  // Draw particles
    ofSetColor(100, 200, 255);
    ofBeginShape();
    for (auto& p : particles) {
        ofCurveVertex(p.pos);
    }
    ofEndShape();

  // Draw blob
    ofSetColor(150, 200, 200);
    ofPath pl;
    //pl.moveTo(ofPoint(particles[0].pos));
    for (auto& p : particles) {
        pl.curveTo(ofPoint(p.pos));
    }
    pl.close();
    pl.draw();


    // Draw target
    ofSetColor(255, 100, 100);
    ofNoFill();
    ofDrawCircle(target, 15);
    ofDrawCircle(target, 10);
    ofFill();
    ofDrawCircle(target, 5);
    
    // Instructions
    ofSetColor(255);
    ofDrawBitmapString("Click to move target", 10, 20);
    ofDrawBitmapString("Press SPACE to create new blob", 10, 40);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 10, 60);
}

void ofApp::keyPressed(int key) {
    if (key == ' ') {
        createBlob(ofVec2f(ofGetWidth()/2, ofGetHeight()/2), blobRadius, 20);
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    target.set(x, y);
}