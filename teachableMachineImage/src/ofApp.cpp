#include "ofApp.h"


string lastError = "";

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(20);

	// 1. Initialize Webcam
	// We try to get a decent resolution
	vidGrabber.setVerbose(true);
	vidGrabber.setup(640, 480);

	// 2. Load Labels
	// You must create this file manually or copy it from the TM export
	ofBuffer buffer = ofBufferFromFile("model/labels.txt");
	for (auto line : buffer.getLines()) {
		if (line.size() > 0) labels.push_back(line);
	}

	// 3. Load Model
	// Make sure your unzipped "SavedModel" folder is in bin/data/model/
	if (!model.load("model")) {
		cout << "Failed to load model! Check bin/data/model folder.";
		ofSystemAlertDialog("Model failed to load. Check console.");
	} else {
		// --- AUTO-DETECT LAYER NAMES ---
		// The default runModel() guesses names, which causes your error.
		// We will search the model for the correct names.

		//std::vector<std::string> ops = model.get_operations();
		inputOpName = "serving_default_input_1";
		outputOpName = "StatefulPartitionedCall";
		vector<string> inputNames = { inputOpName };
		vector<string> outputNames = { outputOpName };

		model.setup(inputNames, outputNames);
		model.printOperations();

		//// specific strings common in Teachable Machine models
		//bool foundInput = false;
		//bool foundOutput = false;

		//ofLogNotice("Model Ops") << "--- Scanning for Input/Output Layers ---";

		//for (auto op : ops) {
		//	// SEARCH FOR INPUT
		//	// Look for "input" in the name, usually starts with "serving_default_"
		//	if (!foundInput && op.find("input") != string::npos && op.find("serving_default") != string::npos) {
		//		inputOpName = op;
		//		foundInput = true;
		//		ofLogNotice("Auto-Detect") << "Found Input Layer: " << inputOpName;
		//	}

		//	// SEARCH FOR OUTPUT
		//	// Usually "StatefulPartitionedCall" or "Identity" or "dense"
		//	if (!foundOutput) {
		//		if (op.find("StatefulPartitionedCall") != string::npos) {
		//			outputOpName = op;
		//			foundOutput = true;
		//			ofLogNotice("Auto-Detect") << "Found Output Layer: " << outputOpName;
		//		} else if (op.find("Identity") != string::npos) {
		//			outputOpName = op;
		//			foundOutput = true;
		//			ofLogNotice("Auto-Detect") << "Found Output Layer: " << outputOpName;
		//		}
		//	}
		//}

		//// Fallbacks if search failed (prevents crash with empty strings)

	}

	// 4. Allocate the input image container (standard TM size)
	inputImage.allocate(224, 224, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::update() {
	vidGrabber.update();

	if (vidGrabber.isFrameNew()) {

		// --- PRE-PROCESSING ---

		// 1. Crop to Square (Center Crop)
		// Teachable Machine expects a square image. If we squash 640x480
		// into 224x224, the aspect ratio gets weird and accuracy drops.
		ofPixels pixels = vidGrabber.getPixels();
		int minDim = (pixels.getWidth() < pixels.getHeight() ? pixels.getWidth() : pixels.getHeight());
		int startX = (pixels.getWidth() - minDim) / 2;
		int startY = (pixels.getHeight() - minDim) / 2;

		pixels.crop(startX, startY, minDim, minDim);

		// 2. Resize to Model Input Size (224x224)
		pixels.resize(224, 224);
		pixels.mirror(false, true); 
		inputImage.setFromPixels(pixels); // Update our display image

		// 3. Convert to Tensor & Normalize
		// Teachable Machine (standard) uses values between -1 and 1 (or 0-1 depending on version).
		// ofxTF2::pixelsToTensor handles basic conversion, but we might need manual mapping
		// if the defaults don't work. The default usually maps 0-255 to 0.0-1.0.
		// Note: Some TM exports expect (val - 127.5) / 127.5.
		// Let's try the standard 0-1 mapping first which ofxTF2 provides nicely.

		cppflow::tensor inputTensor = ofxTF2::pixelsToTensor(inputImage.getPixelsRef());

        // CRITICAL FIX: Add the batch dimension.
		// The model expects [1, 224, 224, 3], but we have [224, 224, 3].
		inputTensor = cppflow::expand_dims(inputTensor, 0);

        try {
			// Run the model
			auto output = model.runModel(inputTensor);

			// interpret the output
			auto maxLabel = cppflow::arg_max(output, 1);

			// --- POST-PROCESSING ---
			// Convert output tensor back to a vector of floats
			//ofxTF2::tensorToVector(outputTensor, results);

			            // Debug: Print shape if results remain empty
			

			lastError = ""; // Clear error if successful

		} catch (const std::exception & e) {
			lastError = string(e.what());
			ofLogError() << "TensorFlow Error: " << lastError;
			results.clear();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	// Draw the original webcam feed
	ofSetColor(255);
	vidGrabber.draw(0, 0);

	// Draw the "Computer Vision" view (what the AI actually sees)
	// usually small 224x224 image
	float previewX = 650;
	float previewY = 20;
	ofDrawBitmapString("AI Input (224x224):", previewX, previewY - 5);
	inputImage.draw(previewX, previewY);
	ofNoFill();
	ofSetColor(255, 255, 0);
	ofDrawRectangle(previewX, previewY, 224, 224);

	// Draw Results
	if (results.size() > 0) {
		int bestIndex = getHighestProbIndex();

		float barX = 20;
		float barY = 500;
		float barH = 30;
		float barMaxW = 400;

		for (size_t i = 0; i < results.size(); i++) {

			// Check bounds for labels
			string labelName = (i < labels.size()) ? labels[i] : "Class " + ofToString(i);
			float confidence = results[i]; // 0.0 to 1.0

			// Color highlight for the winner
			if (i == bestIndex)
				ofSetColor(0, 255, 0);
			else
				ofSetColor(200);

			// Draw Label text
			ofDrawBitmapString(labelName + ": " + ofToString(confidence * 100, 1) + "%", barX, barY + (i * 50) - 5);

			// Draw Bar background
			ofSetColor(50);
			ofDrawRectangle(barX, barY + (i * 50), barMaxW, barH);

			// Draw Bar foreground
			if (i == bestIndex)
				ofSetColor(0, 255, 0);
			else
				ofSetColor(100, 150, 255);

			ofFill();
			ofDrawRectangle(barX, barY + (i * 50), barMaxW * confidence, barH);
		}

		// Draw BIG result overlay
		ofSetColor(0, 0, 0, 150);
		ofDrawRectangle(0, 0, ofGetWidth(), 40);
		ofSetColor(255);
		string bestLabel = (bestIndex < labels.size()) ? labels[bestIndex] : "Unknown";
		ofDrawBitmapString("PREDICTION: " + bestLabel, 20, 25);
	}
}

//--------------------------------------------------------------
int ofApp::getHighestProbIndex() {
	int maxIndex = 0;
	float maxVal = 0;
	for (int i = 0; i < results.size(); i++) {
		if (results[i] > maxVal) {
			maxVal = results[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
}
