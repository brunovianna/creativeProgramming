#pragma once
#include "ofMain.h"
#include "Particle.h"

class Train {
public:
    string id;
    string lin;
    ofPoint pos;        // Current screen position
    ofPoint targetPos;  // Where the API says we should be
    ofVec2f vel;        // Calculated velocity
    
    vector<Particle> trail;
    ofColor trainColor;

    Train(string _id, string _line, ofPoint _startPos) {
        id = _id;
        lin = _line;
        pos = _startPos;
        targetPos = _startPos;
        // FGC Orange color for the head
        trainColor = ofColor(255, 140, 0); 
    }

    void update(ofPoint newTarget) {
        targetPos = newTarget;
        
        // Smooth movement: Move 10% of the way to the target per frame
        // This prevents the train from "teleporting" when the API updates
        ofPoint oldPos = pos;
        pos.interpolate(targetPos, 0.5);
        
        // Calculate velocity based on movement
        vel = pos - oldPos;
        //pos = nextPos;

        // 1. Add Trail Particles
        // Only add trail if moving
        if (vel.length() > 0.001) {
            // Add a particle at current position with slight random offset
            ofVec2f randomOffset(ofRandom(-1, 1), ofRandom(-1, 1));
            // Trail particles move slowly opposite to train
            ofVec2f trailVel = -vel * 0.1; 
            
            trail.push_back(Particle(pos + randomOffset, trailVel, ofColor(255, 100, 0), 0.02, 8.0));
        }

        // 2. Update Trail Particles
        for (int i = trail.size() - 1; i >= 0; i--) {
            trail[i].update();
            if (trail[i].isDead()) {
                trail.erase(trail.begin() + i);
            }
        }

    }

    void draw() {
        // Draw Trail
        for (auto &p : trail) {
            p.draw();
        }

        // Draw Train Head (Glowing Comet)
        ofSetColor(255, 200, 150); // Brighter center
        ofDrawCircle(pos, 4);
        
        // Optional: Draw ID text
        ofSetColor(255);
        ofDrawBitmapString(lin, pos.x + 10, pos.y - 10);
    }
};