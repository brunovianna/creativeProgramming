#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0); // Black background
    ofSetFrameRate(60);

    // --- Set Lorenz Parameters ---
    // These are the "classic" chaotic values
    sigma = 10.0;
    rho = 28.0;
    beta = 8.0 / 3.0;
    dt = 0.01; // Time step
    
    numParticles = 5000; // Number of particles to trace

    // We'll draw all particles as points
    mesh.setMode(OF_PRIMITIVE_POINTS);

    // Set up our particles
    initializeParticles();
}

//--------------------------------------------------------------
void ofApp::initializeParticles() {
    // Clear old data
    particles.clear();
    mesh.clear();

    // Create new particles
    for (int i = 0; i < numParticles; i++) {
        Particle p;
        
        // Start near the origin, but with slight random variations
        // This makes the attractor "grow" in a nice way
        p.pos = glm::vec3(
            ofRandom(-900, 900),
            ofRandom(-900, 900),
            ofRandom(-900, 900)
        );
        
        // Set an initial color (will be updated)
        p.color.set(255);
        
        // Add the particle to our list
        particles.push_back(p);
        
        // Add its position and color to the mesh
        mesh.addVertex(p.pos);
        mesh.addColor(p.color);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // Get direct access to the mesh's vertices and colors
    auto& vertices = mesh.getVertices();
    auto& colors = mesh.getColors();

    // Update each particle
    for (int i = 0; i < particles.size(); i++) {
        
        // Get a reference to the particle and its current position
        Particle& p = particles[i];
        float x = p.pos.x;
        float y = p.pos.y;
        float z = p.pos.z;

        // --- Lorenz Equations ---
        // Calculate the "velocity" (change in position)
        float dx = (sigma * (y - x)) * dt;
        float dy = (x * (rho - z) - y) * dt;
        float dz = (x * y - beta * z) * dt;

        // Apply the velocity to update the particle's position
        p.pos.x += dx;
        p.pos.y += dy;
        p.pos.z += dz;
        
        // Update the particle's color based on its z-position
        // We map the z-range (approx 0-50) to a hue range (e.g., blue to red)
        p.color.setHsb(ofMap(p.pos.z, 0, 50, 150, 255, true), 200, 255);

        // Update the mesh with the new position and color
        vertices[i] = p.pos;
        colors[i] = p.color;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest(); // Enable 3D depth

    // Start our 3D camera
    cam.begin();
    
    // The attractor's natural size is around 40x40x50 units.
    // We scale it up and translate it to center it in the view.
    ofScale(5, 5, 5); // Make it 5x bigger
    ofTranslate(0, 0, -30); // Center the z-axis
    
    glPointSize(2); // Make the points slightly larger
    
    // Draw the entire mesh of particles in one go
    mesh.draw();
    
    // End the camera
    cam.end();
    
    ofDisableDepthTest(); // Disable 3D depth

    // Draw help text
    ofSetColor(255);
    ofDrawBitmapString("Lorenz Attractor", 20, 20);
    ofDrawBitmapString("Particles: " + ofToString(numParticles), 20, 40);
    ofDrawBitmapString("Press 'r' to reset", 20, 60);
    ofDrawBitmapString("Drag mouse to rotate", 20, 80);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r' || key == 'R') {
        initializeParticles(); // Reset the simulation
    }
}