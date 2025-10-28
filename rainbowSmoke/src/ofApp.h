#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;

		void keyPressed(int key) override;
		// Add other event handlers if needed (mouse, etc.)
		// void keyReleased(int key) override;
		// void mouseMoved(int x, int y ) override;
		// void mouseDragged(int x, int y, int button) override;
		// void mousePressed(int x, int y, int button) override;
		// void mouseReleased(int x, int y, int button) override;
		// void mouseEntered(int x, int y) override;
		// void mouseExited(int x, int y) override;
		// void windowResized(int w, int h) override;
		// void dragEvent(ofDragInfo dragInfo) override;
		// void gotMessage(ofMessage msg) override;
		
		// Helper function to visit and color a pixel
		void visit(int x, int y, unsigned char r, unsigned char g, unsigned char b);

		// Function to reset the simulation
		void reset();

		// ofPixels object to store our pixel data (like ImageData)
		ofPixels image;
		
		// ofTexture to draw the pixels to the screen efficiently
		ofTexture texture;

		// A vector to store the indices of "frontier" pixels (the processing list)
		vector<int> indexes;

		// Variables to store the width and height of our image
		int w, h;
};
