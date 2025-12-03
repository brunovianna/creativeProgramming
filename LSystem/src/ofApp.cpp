#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

  ofSetFrameRate(24);

  //map<string, string> rules = {{"F", "FF+[+F-F-F]-[-F+F+F]"}};
  //map<string, string> rules = {{"X", "XFYFX+F+YFXFY-F-XFYFX"},{"Y", "YFXFY-F-XFYFX+F+YFXFY"}}; // peano
  //map<string, string> rules = {{"F", "F-G+F+G-F"}, {"G", "G+F-G-F+G"}}; // Sierpinski Gasket variation
  map<string, string> rules = {{"A", "+BF-AFA-FB+"},{"B","-AF+BFB+FA-"}};

  lsystem.setup("A", rules);
  turtle.setup(6, ofDegToRad(90.0));

  for (int i = 0; i < 7; ++i) {
    lsystem.generate();
  }

  // Build the path once in setup (more efficient)
  turtle.render(lsystem.sentence);

  // get the line
  bigLine = turtle.getPath().getOutline()[0]; //dealing with only one line for now


}

//--------------------------------------------------------------
void ofApp::update() { 
   ofBackground(255);

 // Add new reveals randomly
    if (reveals.size() < maxReveals) {
        if (ofRandom(1.0) > 0.97) { // Slightly higher probability
            // Choose a random starting point
            float startPercent = ofRandom(1.0);
            
            // Choose a random color
            ofColor randomColor;
            randomColor.setHsb(ofRandom(255), 200, 200);
            
            // Add a new reveal
            reveals.push_back(Reveal(startPercent, bigLine, randomColor, 2, ofRandom (-0.0001,0.0001)));
        }
    }

    // Update all reveals
    for (auto& r : reveals) {
        r.update();
    }


 }

//--------------------------------------------------------------
void ofApp::draw() {
  
  ofPushMatrix();
  ofSetColor(0);
  ofTranslate(20, ofGetHeight()-20);
  //bigLine.draw();


  
  for (auto& r:reveals) {
    r.draw();
  }


  
}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
