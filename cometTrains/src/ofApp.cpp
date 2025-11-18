#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(20); // Dark background
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    //ofSetBackgroundAuto(false);
    
    // Register URL loader callback
    ofRegisterURLNotification(this);
    
    if(!USE_SIMULATION_MODE){
        // Initial load
        ofLoadURLAsync(apiCallURL, "fgc_data");
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // 1. API LOOP (Every 5 seconds)
    if(!USE_SIMULATION_MODE){
        if (ofGetElapsedTimef() - lastApiCallTime > 120.0) {
            ofLoadURLAsync(apiCallURL, "fgc_data");
            lastApiCallTime = ofGetElapsedTimef();
        }
    } else {
        // SIMULATION: Create fake trains moving in sinewaves to test sparks
        // This block is just for testing visuals
        float time = ofGetElapsedTimef();
        vector<string> ids = {"T1", "T2", "T3", "T4"};
        for(int i=0; i<ids.size(); i++){
            float x = ofMap(i, 0, ids.size(), 100, ofGetWidth()-100);
            // Move up and down
            float y = ofGetHeight()/2 + sin(time * 2 + i) * 200; 
            ofPoint simPos(x, y);
            
            if(trains.find(ids[i]) == trains.end()){
                trains.insert(make_pair(ids[i], Train(ids[i], ids[i],simPos)));
            } else {
                trains.at(ids[i]).update(simPos);
            }
        }
    }

    // 2. UPDATE TRAINS & CHECK COLLISIONS
    // We use an iterator to loop through the map
    for (auto& t : trains) {
        // Note: The position update happens inside parseData or the sim loop
        // But we ensure the internal particles update here if not simulated
        if(!USE_SIMULATION_MODE) {
             // We interpret the targetPos set in parseData inside the Draw loop 
             // but actually, let's ensure we call update() on existing trains logic
             // The `update` in Train.h handles the smoothing to target.
             // So we pass the current target to itself to keep smoothing active
             t.second.update(t.second.targetPos);
        }
    }
    
    // 3. COLLISION DETECTION (Sparks)
    // Check every train against every other train
    for (auto it1 = trains.begin(); it1 != trains.end(); ++it1) {
        for (auto it2 = trains.begin(); it2 != trains.end(); ++it2) {
            
            // Don't check same train
            if (it1->first == it2->first) continue;
            
            Train& t1 = it1->second;
            Train& t2 = it2->second;
            
            // Calculate Distance
            float dist = t1.pos.distance(t2.pos);
            
            if (dist < 20.0) { // If closer than 20 pixels
                
                // Check Direction (Dot Product)
                // result < 0 means they are facing opposite directions
                // result > 0 means they are moving generally same direction
                float dot = t1.vel.normalized().dot(t2.vel.normalized());
                
                // If moving opposite directions (crossing)
                if (dot < -0.5) {
                    // Find midpoint for explosion
                    ofPoint midPoint = (t1.pos + t2.pos) / 2;
                    addExplosion(midPoint);
                }
            }
        }
    }

    // 4. UPDATE SPARKS
    for (int i = sparks.size() - 1; i >= 0; i--) {
        sparks[i].update();
        if (sparks[i].isDead()) {
            sparks.erase(sparks.begin() + i);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // Use Additive Blending for "Glowing" effect
    
    // ofSetColor(20,20);
    // ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    // Draw Trains
    for (auto& t : trains) {
        t.second.draw();
    }

    // Draw Sparks
    for (auto& s : sparks) {
        s.draw();
    }

    ofDisableBlendMode();
    
    // Draw Debug Info
    ofSetColor(255);
    ofDrawBitmapString("Active Trains: " + ofToString(trains.size()), 20, 20);
    if(USE_SIMULATION_MODE) ofDrawBitmapString("SIMULATION MODE", 20, 40);
}

//--------------------------------------------------------------
void ofApp::urlResponse(ofHttpResponse & response) {
    cout << "response " << response.status << "\n";



    if (response.status == 200) {
        ofJson json = ofJson::parse(response.data);
        
        // The FGC API structure usually looks like:
        // { "records": [ { "fields": { "id": "...", "lat": ..., "lon": ... } }, ... ] }
        
        if (json.contains("results")) {
            for (auto& record : json["results"]) {

                    
                    string id = record["id"].get<string>();

                    //DEBUG
                    if (debugTrainId == "") debugTrainId = id;
           


                    string lin = record["lin"].get<string>();
                    ofJson geoPoint = record["geo_point_2d"];
                    float lat = geoPoint["lat"].get<float>();
                    float lon = geoPoint["lon"].get<float>();
                    
                    if (id == debugTrainId) cout << lat << " " << lon << "\n";

                    // MAP GPS TO SCREEN
                    // Note: Map Y is usually inverted (Lat goes up, Screen Y goes down)
                    float x = ofMap(lon, minLon, maxLon, 0, ofGetWidth());
                    float y = ofMap(lat, minLat, maxLat, ofGetHeight(), 0);
                    ofPoint newPos(x, y);
                    
                    // Create or Update
                    if (trains.find(id) == trains.end()) {
                        // New Train
                        trains.insert(make_pair(id, Train(id,  lin, newPos)));
                    } else {
                        // Existing Train - Update Target
                        trains.at(id).update(newPos);
                    }
                
            }
        }
    } else {
        ofLog(OF_LOG_ERROR, "API Request Failed");
    }
}

//--------------------------------------------------------------
void ofApp::addExplosion(ofPoint p) {
    // Create a burst of particles
    for (int i = 0; i < 20; i++) {
        ofVec2f vel(ofRandom(-5, 5), ofRandom(-5, 5));
        // White/Yellow sparks, fast decay
        sparks.push_back(Particle(p, vel, ofColor(255, 255, 200), 0.05, 2.0));
    }
}