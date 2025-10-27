#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){





	glm::vec2 p1(0,0);
    glm::vec2 p2(1000,0);
	glm::vec2 p3(0,1000);


    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA); 
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofFill();
    fbo.begin();
    splitAndDraw (Triangle(p1,p2,p3));
    p1.x=1000;
    p1.y=1000;
    splitAndDraw (Triangle(p1,p2,p3));
    fbo.end();


}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    

    fbo.draw(0,0);
    


}

void ofApp::splitAndDraw(Triangle _t) {


    vector <int> els =  {0,1,2};
    int lefOutIndex = ofRandom(3);
    glm::vec leftOut = _t.points[lefOutIndex];
    els.erase(els.begin()+lefOutIndex);

    glm::vec2 p1 = _t.points[els[0]];
    glm::vec2 p2 = _t.points[els[1]];

    float a = _t.area();
    
    //ofSetColor(255,100);
    ofPath p;
    p.setFilled(true);
    //p.setColor(ofColor(200,0,0));
    //p.setStrokeWidth(1);
    //p.setFillColor(ofColor(255*ofNoise(counter*0.005)));
    p.setFillColor(ofColor(ofRandom(50,200)));
    //p.setFillColor(ofColor(ofMap(a,500000,5000,0,255)));
    p.triangle(p1,p2,leftOut);
    p.close();
    //cout << counter++ << " "<<a << "\n";
    p.draw();

    //ofDrawTriangle(p1,p2,leftOut);



    //glm::vec halfVect = p2 - p1;
    //float newLength = glm::length(halfVect);

    if (a > 10000) {
       
//    if (newLength > 100) {
       glm::vec2 new_point = (p1 + p2)*0.5;
       splitAndDraw(Triangle(new_point,p1,leftOut));
       splitAndDraw(Triangle(new_point,p2,leftOut));

    //     glm::vec2 diff = p2 - p1;
    //     glm::vec2 point1 = p1 + diff * 0.33;
    //     glm::vec2 point2 = p1 + diff * 0.66;
    //    splitAndDraw(Triangle(point1,p1,leftOut));
    //    splitAndDraw(Triangle(point1,point2,leftOut));
    //    splitAndDraw(Triangle(point2,p2,leftOut));

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
