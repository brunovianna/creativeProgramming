#pragma once

#include "ofMain.h"
#include "ofxTensorFlow2.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);

	// Core OF objects
	ofVideoGrabber vidGrabber;

	// AI Objects
	ofxTF2::Model model;


	// Variables to store the correct layer names

	std::string inputOpName;
	std::string outputOpName;
	// Data handling
	ofImage inputImage; // The resized image we feed to the AI (224x224)
	vector<float> results; // The raw probabilities
	vector<string> labels; // The class names (from labels.txt)

	// Helper to sort predictions
	int getHighestProbIndex();
};
