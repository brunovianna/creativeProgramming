#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    // physics
    ofVec2f pos, vel, acc;
    float mass;
    float gravity;
    float friction;
    bool mouseHeld;
};
