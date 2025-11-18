#pragma once

#include "ofMain.h"

// A simple struct to hold our particle's data
struct Particle {
    glm::vec3 pos;  // Current position
    ofColor color;  // Particle color
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    // Helper function to set up or reset particles
    void initializeParticles();

    // --- Particle System ---
    vector<Particle> particles;
    ofVboMesh mesh; // Use a VBO mesh for fast drawing
    int numParticles;

    // --- 3D Camera ---
    ofEasyCam cam;

    // --- Lorenz Attractor Parameters ---
    float sigma;
    float rho;
    float beta;
    float dt; // Time step for the simulation
};