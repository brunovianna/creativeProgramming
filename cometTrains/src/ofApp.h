#pragma once

#include "ofMain.h"
#include "Train.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    // API Handling
    void urlResponse(ofHttpResponse & response);
    void parseData();
    
    // Global Spark System (Explosions)
    vector<Particle> sparks;
    void addExplosion(ofPoint p);

    // Map management
    std::map<string, Train> trains; // Store trains by ID
    
    // Coordinates for Barcelona/FGC Area (Approximate)
    // Adjust these to zoom in/out on the map
    float minLat = 41.25;
    float maxLat = 41.60;
    float minLon = 1.95;
    float maxLon = 2.25;
    
    // Timer for API calls
    float lastApiCallTime;
	string apiCallURL = "https://dadesobertes.fgc.cat/api/explore/v2.1/catalog/datasets/posicionament-dels-trens/records?limit=100";
    
    // IMPORTANT: Set this to false to use real data
    // Set to true to test the visuals without internet/API
    bool USE_SIMULATION_MODE = false; 

	string debugTrainId = "";
};