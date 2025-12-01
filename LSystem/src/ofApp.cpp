#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  //map<string, string> rules = {{"F", "FF+[+F-F-F]-[-F+F+F]"}};
  //map<string, string> rules = {{"X", "XFYFX+F+YFXFY-F-XFYFX"},{"Y", "YFXFY-F-XFYFX+F+YFXFY"}}; // peano
  //map<string, string> rules = {{"F", "F-G+F+G-F"}, {"G", "G+F-G-F+G"}}; // Sierpinski Gasket variation
  map<string, string> rules = {{"A", "+BF-AFA-FB+"},{"B","-AF+BFB+FA-"}};

  lsystem.setup("A", rules);
  turtle.setup(12, ofDegToRad(90.0));

  for (int i = 0; i < 6; ++i) {
    lsystem.generate();
  }

}

//--------------------------------------------------------------
void ofApp::update() { ofBackground(255); }

//--------------------------------------------------------------
void ofApp::draw() {
   ofSetColor(0);
  ofTranslate(ofGetWidth()*0+24, ofGetHeight()*1-24);
  turtle.render(lsystem.sentence);
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
