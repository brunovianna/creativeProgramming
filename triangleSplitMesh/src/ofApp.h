#pragma once

#include "ofMain.h"

// 1. Define a Triangle struct that uses glm::vec3
struct Triangle {
    glm::vec3 points[3];

    Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) {
        points[0] = p1;
        points[1] = p2;
        points[2] = p3;
    }

    // Area calculation is still based on the 2D (x, y) projection
    float area() {
        glm::vec2 p1(points[0].x, points[0].y);
        glm::vec2 p2(points[1].x, points[1].y);
        glm::vec2 p3(points[2].x, points[2].y);
        
        return 0.5 * abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
    }
};


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        // 2. The recursive function now takes our 3D Triangle struct
        void splitAndAdd(Triangle _t);

        // 3. Declare the mesh and a camera
        ofMesh mesh;
        ofEasyCam cam;
    
        // 4. (Optional) Counter for debugging
        int counter = 0;

        ofLight pointLight;
};