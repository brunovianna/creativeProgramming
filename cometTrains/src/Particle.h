#pragma once
#include "ofMain.h"

class Particle {
public:
    ofPoint pos;
    ofVec2f vel;
    ofColor color;
    float life;      // 1.0 = full life, 0.0 = dead
    float decay;     // How fast it fades
    float size;

    Particle(ofPoint _pos, ofVec2f _vel, ofColor _col, float _decay, float _size) {
        pos = _pos;
        vel = _vel;
        color = _col;
        decay = _decay;
        size = _size;
        life = 1.0;
    }

    void update() {
        pos += vel;
        life -= decay;
    }

    void draw() {
        if (life > 0) {
            ofSetColor(color, 255 * life); // Fade out alpha
            ofDrawCircle(pos, size * life); // Shrink slightly as it dies
        }
    }

    bool isDead() {
        return life <= 0;
    }
};