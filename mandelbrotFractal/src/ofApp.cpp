#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Mandelbrot Fractal");
	ofBackground(0); // Black background
	ofSetFrameRate(60);

	// Allocate our image to the size of the window
	mandelbrotImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_COLOR);

	// Set initial values
	maxIterations = 100;
	
	// Set the initial range of the complex plane to view
	// We calculate a width that matches our 4:3 aspect ratio
	minImag = -1.5;
	maxImag = 1.5;
	double rangeImag = maxImag - minImag; // 3.0
	double rangeReal = rangeImag * (double)ofGetWidth() / (double)ofGetHeight(); // 3.0 * (800/600) = 4.0

	// Center the real range around -0.5
	minReal = -0.5 - (rangeReal / 2.0); // -0.5 - 2.0 = -2.5
	maxReal = -0.5 + (rangeReal / 2.0); // -0.5 + 2.0 = 1.5

	// Generate the first fractal image
	generateMandelbrot();
}

//--------------------------------------------------------------
void ofApp::generateMandelbrot() {
	
	int w = mandelbrotImage.getWidth();
	int h = mandelbrotImage.getHeight();

	// Loop through every pixel
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {

			// Map the pixel (x, y) to a complex number 'c' = (a, b)
			// a = real part, b = imaginary part
			double a = ofMap(x, 0, w, minReal, maxReal);
			double b = ofMap(y, 0, h, minImag, maxImag);

			// Store 'c'
			double ca = a;
			double cb = b;

			// Iteration variables for 'z'
			double za = 0.0;
			double zb = 0.0;

			int n = 0; // Iteration counter

			// Start the Mandelbrot iteration
			// z_n+1 = z_n^2 + c
			while (n < maxIterations) {
				// Calculate z^2 = (za + zb*i)^2 = (za*za - zb*zb) + (2*za*zb)*i
				double za_new = za * za - zb * zb;
				double zb_new = 2 * za * zb;

				// Add c
				za = za_new + ca;
				zb = zb_new + cb;

				// Check if the magnitude |z| has escaped the boundary
				// We check |z|^2 > 4 (which is |z| > 2) to avoid a slow sqrt()
				if (za * za + zb * zb > 4.0) {
					break; // Escaped!
				}

				n++;
			}

			// We have our 'n'. Now map it to a color.
			ofColor color;
			if (n == maxIterations) {
				// We are *inside* the set
				color.set(0, 0, 0); // Black
			} else {
				// We are *outside* the set.
				// Color based on how many iterations it took to escape.
				// We use HSB color for a smooth rainbow effect.
				float hue = ofMap(n, 0, maxIterations, 0, 255);
				float saturation = 255;
				float brightness = 200;
				color = ofColor::fromHsb(hue, saturation, brightness);
			}

			// Set the pixel in our image
			mandelbrotImage.setColor(x, y, color);
		}
	}

	// Update the image's internal texture to prepare for drawing
	mandelbrotImage.update();
	ofLog() << "Mandelbrot generated with maxIterations: " << maxIterations;
}


//--------------------------------------------------------------
void ofApp::update() {
	// Nothing to do here, all calculation is on-demand
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Draw the pre-calculated image
	mandelbrotImage.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'r' || key == 'R') {
		// Reset the view and iterations
		ofLog() << "Resetting view.";
		maxIterations = 100;
		minImag = -1.5;
		maxImag = 1.5;
		double rangeImag = maxImag - minImag;
		double rangeReal = rangeImag * (double)ofGetWidth() / (double)ofGetHeight();
		minReal = -0.5 - (rangeReal / 2.0);
		maxReal = -0.5 + (rangeReal / 2.0);
		
		// Regenerate the image
		generateMandelbrot();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (button == OF_MOUSE_BUTTON_LEFT) {
		ofLog() << "Zooming in at (" << x << ", " << y << ")";

		// Map the mouse click to a complex coordinate
		double mouseReal = ofMap(x, 0, ofGetWidth(), minReal, maxReal);
		double mouseImag = ofMap(y, 0, ofGetHeight(), minImag, maxImag);

		// Define how much to zoom
		double zoomFactor = 2.0;
		
		// Increase detail as we zoom
		maxIterations += 50; 

		// Calculate the old range
		double oldRangeReal = maxReal - minReal;
		double oldRangeImag = maxImag - minImag;

		// Calculate the new, smaller range
		double newRangeReal = oldRangeReal / zoomFactor;
		double newRangeImag = oldRangeImag / zoomFactor;

		// Set the new min/max, centered on the mouse click
		minReal = mouseReal - (newRangeReal / 2.0);
		maxReal = mouseReal + (newRangeReal / 2.0);
		minImag = mouseImag - (newRangeImag / 2.0);
		maxImag = mouseImag + (newRangeImag / 2.0);

		// Regenerate the fractal
		generateMandelbrot();
	}
}


//--- Unused Event Handlers ------------------------------------

void ofApp::keyReleased(int key) {}
void ofApp::mouseMoved(int x, int y) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}