/*
 * Code example for The Nature of Code (2024 Edition)
 * (https://natureofcode.com/)
 * Ported from p5.js by Jack B. Du
 * (https://github.com/jackbdu/nature-of-code-2024-openframeworks)
 */

#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {

	ofSetupOpenGL(800,800,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
