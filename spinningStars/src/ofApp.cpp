#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
    myStar.update();

    for (Star &b : myStars) {
        b.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){


    int i=0;
    for (Star b : myStars) {
        b.display();

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



    Star b;
    b = Star(ofRandomWidth(),ofRandomHeight());
    myStars.push_back(b);
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



ofPolyline ofApp::star(int radius) {



    ofPolyline _star;
    _star.begin();
    for (int i=0;i<5;i++){
        float x = radius * cos(ofDegToRad(i*72-36));
        float y = radius * sin(ofDegToRad(i*72-36));
        _star.addVertex(x,y);
        x = radius * 0.4 * cos(ofDegToRad(i*72));
        y = radius * 0.4 * sin(ofDegToRad(i*72));
        _star.addVertex(x,y);
    }
    _star.close();


    return(_star);

}


Star::Star() {
    location = ofVec2f(ofRandom((float)(ofGetWindowWidth()/2)),ofRandom((float)(ofGetWindowHeight()/2)));
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    colour = ofColor (ofRandom(256)); 
    size = 10;
};

Star::Star(int _x, int _y) { //same name, different parameters
    location = ofVec2f(_x,_y);
    velocity = ofVec2f(ofRandom(-3,3),ofRandom(-3,3));
    colour = ofColor (ofRandom(256)); 
    size = 10;
};


void Star::display() {
    ofSetColor (colour);
    ofDrawCircle(location.x, location.y, size);
    cout << "speed: " << velocity.x << " " << velocity.y << "\n";
};

void Star::update() {

    int newX = location.x + velocity.x ;
    if ((newX> 0)&&(newX< ofGetWidth())) {
        location.x = newX;
        cout << "updatex: " << location.x << "\n";
    } else {
        velocity.x = -velocity.x;
        location.x = location.x + velocity.x ;
         
    }

    int newY = location.y + velocity.y ;
    if ((newY> 0)&&(newY< ofGetHeight())) {
        location.y = newY;
    } else {
        velocity.y = -velocity.y;
        location.y = location.y + velocity.y ;
    }

};