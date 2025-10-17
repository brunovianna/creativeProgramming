#include "ofApp.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::setup(){
    pointLight.setup();
    pointLight.setPosition(-100, 200,300);
	pointLight.enable();
    ofEnableLighting();
    ofEnableDepthTest();

	// ofSetSmoothLighting(true);
	// pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
	// pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

    boxMaterial.setDiffuseColor(ofFloatColor::red);
    boxMaterial.setShininess(0.02);

    texture.load("sunset.jpg");
    //texture.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    box.mapTexCoordsFromTexture( texture.getTexture() );
    sph.mapTexCoordsFromTexture( texture.getTexture() );

}
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofFill();
    cam.begin();
    ofSetColor(0,200,0);
    //ofDrawSphere(100,100,0,100.0f);
    texture.getTexture().bind();
    sph.draw();
    texture.getTexture().unbind();
    boxMaterial.begin();
    ofTranslate(300,300);

    box.draw();
    boxMaterial.end();
    cam.end();

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
