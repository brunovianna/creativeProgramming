#pragma once

#include "ofMain.h"

class el2 {

	public:
		float rad;
		ofPoint pos;
		ofPoint vel;
		ofColor col;
		el2();

		void draw();
		void update();
		//void el2(ofPoint _pos, ofPoint _vel, float _rad, ofColor _col); 


};

class intersectionData {
	public:
		ofPoint pos;
		float size;
};

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

		vector <el2> elements;
		vector <intersectionData> intersections;
		

		vector <ofPoint> findCircleIntersections(double x1, double y1, double r1, 
    		double x2, double y2, double r2);
};

