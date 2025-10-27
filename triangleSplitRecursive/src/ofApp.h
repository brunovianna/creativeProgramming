#pragma once

#include "ofMain.h"

class Triangle {


	public:
		Triangle (glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3) {
			points[0] = _p1;			
			points[1] = _p2;			
			points[2] = _p3;			
		}  
		glm::vec2 points[3];


		float area() {
			// Create two vectors representing two edges of the triangle
			glm::vec2 v1 = points[1] - points[0];
			glm::vec2 v2 = points[2] - points[0];

			// Calculate the 2D "cross product" (which is technically the determinant)
			// v1.x * v2.y - v1.y * v2.x
			float crossProduct = (v1.x * v2.y) - (v1.y * v2.x);

			// The area is half the absolute value of the cross product
			return 0.5f * std::abs(crossProduct);
		}


};


class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void splitAndDraw(Triangle _t);
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

    ofFbo fbo;
	int counter;
		
};
