#pragma once

#include "ofMain.h"
#include "ofxSoundObjects.h"


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	// Sound objects
	ofxSoundPlayerObject player;

	ofSoundStream stream;
	ofxSoundOutput output;

	ofSoundBuffer buff;

	// Visualisation variables
	float volume = 0.0f;
	float smoothedVolume = 0.0f;
	ofEasyCam cam;

	// Constants for visualization
	const float volumeSmoothRate = 0.15f; // Slightly increased smoothing
	const float sphereBaseY = 0.0f;
	const float maxSphereMovement = 200.0f; // Increased movement range for impact
};
