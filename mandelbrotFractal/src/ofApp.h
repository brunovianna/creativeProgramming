#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// A helper function to do the fractal calculation
	void generateMandelbrot();

	// The image we will draw the fractal onto
	ofImage mandelbrotImage;

	// Variables to define our view of the complex plane
	// We use double for high precision when zooming
	double minReal;
	double maxReal;
	double minImag;
	double maxImag;

	// The maximum number of iterations to check
	int maxIterations;
};