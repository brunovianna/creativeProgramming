#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Set the width and height from the window dimensions
	w = ofGetWidth();
	h = ofGetHeight();

	// Allocate the ofPixels object with our dimensions and RGBA format
	image.allocate(w, h, OF_PIXELS_RGBA);
	
	// Allocate the texture
	texture.allocate(image);

	// This mimics `imageRendering = "pixelated"` by using nearest-neighbor scaling
	texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	// Set a black background
	ofBackground(0);

	// Start the simulation
	reset();
}

//--------------------------------------------------------------
void ofApp::reset() {
	// Clear all pixels to be fully transparent (alpha = 0)
	image.setColor(ofColor(0, 0, 0, 0));

	// Clear the processing list
	indexes.clear();

	// Start the process at the center pixel with the initial color
	visit(w / 2, h / 2, 128, 128, 128);
}


//--------------------------------------------------------------
void ofApp::visit(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
	// Boundary check: exit if the pixel is outside the image
	if (x < 0 || x >= w || y < 0 || y >= h) return;

	// Check the alpha channel to see if the pixel has been visited
	// ofPixels::getColor() is fast
	if (image.getColor(x, y).a == 0) {
		
		// Calculate the new color with a random jitter of -1 or +1
		// We use (int)ofRandom(2) * 2 - 1 to get either -1 or 1
		unsigned char newR = r + ((int)ofRandom(2) * 2 - 1);
		unsigned char newG = g + ((int)ofRandom(2) * 2 - 1);
		unsigned char newB = b + ((int)ofRandom(2) * 2 - 1);

		// Set the pixel color and make it fully opaque (alpha = 255)
		image.setColor(x, y, ofColor(newR, newG, newB, 255));

		// Calculate the 1D index of this pixel
		int i = y * w + x;
		
		// Add this pixel's index to our processing list
		indexes.push_back(i);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	// Process a batch of pixels each frame to make the simulation run fast
	int stepsPerFrame = 1000;

	for (int frame = 0; frame < stepsPerFrame; ++frame) {
		// If the list is empty, we're done, so stop processing
		if (indexes.empty()) {
			break;
		}

		// 1. Pick a random index `i` from the `indexes` vector
		int i = (int)ofRandom(indexes.size());
        

		// 2. Get the pixel index `j` stored at that vector index
		int j = indexes[i];

		// 3. Perform a fast random removal:
		//    Swap the chosen element with the last element...
		indexes[i] = indexes.back();
		//    ...and then remove the last element (which is now a copy of `indexes[i]`)
		indexes.pop_back();

		// 4. Get the (x, y) coordinates and color of the chosen pixel
		int x = j % w;
		int y = j / w;
		ofColor color = image.getColor(x, y);

		// 5. Visit all four neighbors, passing the current pixel's color
		visit(x - 1, y, color.r, color.g, color.b); // Left
		visit(x + 1, y, color.r, color.g, color.b); // Right
		visit(x, y - 1, color.r, color.g, color.b); // Top
		visit(x, y + 1, color.r, color.g, color.b); // Bottom
	}

	// After processing the batch, update the texture with the new pixel data
	texture.loadData(image);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(255);
	
	// Draw the texture at (0, 0)
	texture.draw(0, 0, w, h);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	// Press 'r' or ' ' (spacebar) to reset the simulation
	if (key == 'r' || key == ' '){
		reset();
	}
}
