#pragma once

#include "ofMain.h"
#include "ofEvents.h"

const int BAUD_RATE = 115200;
const string SERIAL_PORT_NAME = "ACM0"; 

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
	
    ofSerial serial;
    ofEasyCam cam;
    
    // Variables to store the received accelerometer values
    float rotationX = 0.0f;
    float rotationY = 0.0f;
    float rotationZ = 0.0f;
    
    // Buffer for incoming serial data
    string serialBuffer;

	ofLight pointLight;
	ofBoxPrimitive box;
	ofMaterial boxMaterial;

};
