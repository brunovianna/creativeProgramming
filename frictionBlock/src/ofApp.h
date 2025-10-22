#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    // --- Physics Simulation Variables ---
    ofVec2f position;       // Block's current position (center)
    ofVec2f velocity;       // Block's current velocity
    ofVec2f acceleration;   // Block's current acceleration (net force / mass)

    float mass = 10.0f;          // Mass of the block (set to 1.0 for simpler force/acceleration math)
    float blockSize = 50.0f;    // Size of the square block
    float groundLevel;          // Y-coordinate of the ground surface

    // --- Physics Constants ---
    const ofVec2f GRAVITY = ofVec2f(0.0f, 9.8f); // Gravity acceleration (m/s^2)
    const float MOUSE_FORCE_SCALE = 0.05f;       // Scale factor for the mouse-applied force
    const float MU_KINETIC = 0.9f;              // Coefficient of kinetic friction

    // --- Interaction Variables ---
    bool isMousePressed = false;
    ofVec2f mousePos;
    ofVec2f appliedMouseForce;

    // --- Helper Functions ---
    void applyForce(ofVec2f force);
    void drawForceArrow(ofVec2f start, ofVec2f end, ofColor color);
};