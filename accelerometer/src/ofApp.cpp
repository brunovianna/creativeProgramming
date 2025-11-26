#include "ofApp.h"

 void ofApp::setup() {
        ofSetFrameRate(60);
        ofSetWindowTitle("Accelerometer Cube Inclination");

        pointLight.setup();
        pointLight.setPosition(-100, 200,300);
        pointLight.enable();
        ofEnableLighting();
        ofEnableDepthTest();

        boxMaterial.setDiffuseColor(ofFloatColor::red);
        boxMaterial.setShininess(0.02);
        
        // Find and open the serial port
        std::vector<ofSerialDeviceInfo> deviceList = serial.getDeviceList();
        
        bool portFound = false;
        for(auto& device : deviceList) {
            if (ofIsStringInString(device.getDeviceName(), SERIAL_PORT_NAME)) {
                serial.setup(device.getDeviceName(), BAUD_RATE);
                portFound = true;
                ofLogNotice() << "Serial port opened: " << device.getDeviceName();
                break;
            }
        }
        
        if (!portFound) {
            ofLogError() << "Serial port " << SERIAL_PORT_NAME << " not found. Please check device name.";
        }
        
        // Give the Arduino time to initialize
        ofSleepMillis(2000);
    }

    void ofApp::update() {
        // --- 1. Request Data from Arduino ---
        // Send 'R' byte to prompt the Arduino to reply with the current data
        unsigned char request = 'R';
        if (serial.isInitialized()) {
            serial.writeBytes(&request, 1);
        }
        
        // --- 2. Read and Parse Data ---
        // Read all available bytes
        while (serial.available()) {
            // Read a single byte
            char byte = serial.readByte();
            
            // Check for the newline character, which signifies a complete data packet
            if (byte == '\n') {
                // We have a full packet, now parse it (Format: X,Y,Z)
                std::vector<std::string> values = ofSplitString(serialBuffer, ",", true, true);
                
                if (values.size() == 3) {
                    // Convert strings to floats
                    rotationX = ofToFloat(values[0]);
                    rotationY = ofToFloat(values[1]);
                    rotationZ = ofToFloat(values[2]);
                    
                    // Log the received data
                    // ofLogVerbose() << "Received: X=" << rotationX << ", Y=" << rotationY << ", Z=" << rotationZ;
                } else {
                    ofLogWarning() << "Incomplete or badly formatted packet: " << serialBuffer;
                }
                
                // Clear the buffer for the next incoming packet
                serialBuffer = "";
            } else if (byte != OF_SERIAL_ERROR && byte != '\r') {
                // Append all other characters to the buffer, ignoring carriage return
                serialBuffer += byte;
            }
        }
    }

    void ofApp::draw() {
        ofBackground(50, 50, 50);
        ofFill();
        cam.begin();
        


        // --- Apply Rotations and Draw Cube ---
        ofPushMatrix();
        
        // Center the cube
        ofTranslate(0, 0, 0);
        
        // Apply the rotations based on accelerometer data
        // X rotation (Pitch)
        ofRotateDeg(rotationX, 1.0, 0.0, 0.0);
        
        // Y rotation (Roll/Yaw depending on axis mapping)
        ofRotateDeg(rotationY, 0.0, 1.0, 0.0);

        // Z rotation (often Yaw/Roll)
        ofRotateDeg(rotationZ, 0.0, 0.0, 1.0);
        
        ofSetColor(255, 100, 100);
        boxMaterial.begin();
        box.draw();
        boxMaterial.end();
        ofPopMatrix();
        
        cam.end();
        
        // --- On-screen info ---
        ofDisableDepthTest();
        ofSetColor(255);
        ofDrawBitmapString("Rotation X (Pitch): " + ofToString(rotationX, 2), 20, 20);
        ofDrawBitmapString("Rotation Y (Roll): " + ofToString(rotationY, 2), 20, 40);
        ofDrawBitmapString("Rotation Z (Yaw): " + ofToString(rotationZ, 2), 20, 60);
        ofDrawBitmapString("Press and hold mouse to rotate camera.", 20, 80);
    }


//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
