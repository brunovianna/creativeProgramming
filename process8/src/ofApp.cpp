#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){

    int numEls = 4000;
    for (int i=0;i<numEls;i++) {
        el2 e;
        elements.push_back(e);
    }
    ofBackground(255);
    ofSetFrameRate(24);

}

//--------------------------------------------------------------
void ofApp::update(){
    intersections.clear();
    vector <el2> elementscopy = elements;
    int i=0;
    for (el2 &e: elementscopy) {
        for (vector<el2>::iterator it = elementscopy.begin() +i; it != elementscopy.end(); ++it) {
            el2 f = *it;
            vector <ofPoint> newIntersections;
            newIntersections = findCircleIntersections(
                e.pos.x, e.pos.y,e.rad,f.pos.x,f.pos.y,f.rad
            );
            if (!newIntersections.empty()){
                ofPoint a = newIntersections.back();
                newIntersections.pop_back();
                ofPoint b = newIntersections.back();
                float d = ofDist(a.x,a.y,b.x,b.y) * 0.3f;
                intersectionData intA, intB;
                intA.pos = a;
                intA.size = d;
                intersections.push_back(intA); //first point
                intB.pos = b;
                intB.size = d;
                intersections.push_back(intB); //second point
            }
        }
        i++;
        //elementscopy.erase(elementscopy.begin());
    }
    for (el2 &e: elements) {
        e.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    ofSetColor(200,200,0);
    for (el2 &e: elements) {
        e.draw();
    }
    ofFill();
    for (auto p: intersections) {

        ofSetColor(p.size*50);
        ofDrawCircle(p.pos.x,p.pos.y,p.size);
    }
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

el2::el2 () {

    pos = ofPoint (ofRandomWidth(),ofRandomHeight());
    vel = ofPoint (ofRandom(-2,2),ofRandom(-2,2));
    col = ofColor (ofRandom(255));
    rad = ofRandom(3,10);
}

void el2::update() {
    pos += vel;
    if (pos.x  > ofGetWidth() + rad) pos.x = -rad;
    if (pos.y  > ofGetHeight() + rad) pos.y = -rad;
    if (pos.x  < - rad) pos.x = rad + ofGetWidth();
    if (pos.y  < - rad) pos.x = rad + ofGetHeight();

}

void el2::draw() {
    //ofSetColor(col);
    ofDrawCircle (pos,rad);
}


vector <ofPoint> ofApp::findCircleIntersections(double x1, double y1, double r1, 
    double x2, double y2, double r2) {



    vector <ofPoint> intersections;
    // Calculate the distance between the centers of the circles
    double d = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));

    // Check if the circles are separate or if one circle is contained within the other
    if (d > (r1 + r2) || d < std::abs(r1 - r2)) {
        return intersections; // No intersection
    }


    // Calculate intersection points
    // a is the distance from circle 1's center to the line between the intersection points
    double a = (std::pow(r1, 2) - std::pow(r2, 2) + std::pow(d, 2)) / (2 * d);
    
    // h is the height from the line to the intersection points
    double h = std::sqrt(std::pow(r1, 2) - std::pow(a, 2));

    // Find the midpoint between the two centers
    double x0 = x1 + a * (x2 - x1) / d;
    double y0 = y1 + a * (y2 - y1) / d;

    // Calculate the intersection points
    double rx = -(y2 - y1) * (h / d);
    double ry = (x2 - x1) * (h / d);

    intersections.emplace_back(ofPoint(x0 + rx, y0 + ry)); // First intersection point
    intersections.emplace_back(ofPoint(x0 - rx, y0 - ry)); // Second intersection point

    return intersections;
                                                    
}