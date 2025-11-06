#pragma once

#include "ofMain.h"

struct Particle {
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
    float mass;
    bool pinned;
    
    Particle() : mass(1.0f), pinned(false) {}
    
    void applyForce(ofVec2f force) {
        acc += force / mass;
    }
    
    void update(float damping = 0.98f) {
        if (!pinned) {
            vel += acc;
            vel *= damping;
            pos += vel;
        }
        acc.set(0, 0);
    }
};

struct Spring {
    int i, j;
    float restLength;
    float stiffness;
    
    Spring(int _i, int _j, float _restLength, float _stiffness = 0.5f) 
        : i(_i), j(_j), restLength(_restLength), stiffness(_stiffness) {}
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);
    
    void createBlob(ofVec2f center, float radius, int numParticles);
    void applySpringForces();
    void seekTarget();
    void constrainToScreen();
    
    vector<Particle> particles;
    vector<Spring> springs;
    ofVec2f target;
    float seekStrength;
    float blobRadius;
};
