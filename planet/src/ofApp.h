#pragma once

#include "ofMain.h"


	

class Moon {

	public:
		Moon();
		Moon(int x, int y);
		void display();
		void update();
		void applyForce (ofVec2f _force);

		ofVec2f location;
		ofVec2f velocity;
		ofVec2f acceleration;
		ofColor colour;
		float mass;


};


class Planet {

	public:
		Planet();
		Planet(int x, int y);
		void display();
		void update();
		void attract (Moon& _moon);

	private:
		ofVec2f location;
		ofVec2f velocity;
		ofColor colour;
		float mass;
		float gravity = 0.5f;


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
		
		vector <Moon> myMoons;
		Planet planet;

};
