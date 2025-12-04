#pragma once

#include "LSystem.h"
#include "Turtle.h"
#include "ofMain.h"

class Reveal {
  public:
    ofPolyline thisLine, refLine;
    float speed;
    float percent;
    float idx;
    float width;
    ofColor c;
    Reveal (float _percent, ofPolyline& _refLine, ofColor _c, float _width, float _speed) {
      c = _c;
      width = _width;
      refLine = _refLine;
      speed = _speed;
      thisLine.clear();
      
      percent = _percent;
      idx = refLine.getIndexAtPercent(percent );

    }

    void update () {
      float cIdx = refLine.getIndexAtPercent(percent );
      float nIdx = refLine.getIndexAtPercent(percent + speed);
      percent += speed;
      // Clamp percent between 0 and 1
      if (percent > 1.0) percent = 1.0;
      if (percent < 0.0) percent = 0.0;


      if ((int)nIdx!=(int)cIdx) {
        for (int i=(int)cIdx;(int)nIdx!=i;((int)nIdx>(int)cIdx ? i++ : i-- )) {
          thisLine.addVertex(refLine.getVertices()[i]);
        }
      }
    }

    void draw() {
      ofSetColor(c);
      ofSetLineWidth(width);
      thisLine.draw();

    }
};


class ofApp : public ofBaseApp {

public:
  void setup() override;
  void update() override;
  void draw() override;
  void exit() override;

  void keyPressed(int key) override;
  void keyReleased(int key) override;
  void mouseMoved(int x, int y) override;
  void mouseDragged(int x, int y, int button) override;
  void mousePressed(int x, int y, int button) override;
  void mouseReleased(int x, int y, int button) override;
  void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
  void mouseEntered(int x, int y) override;
  void mouseExited(int x, int y) override;
  void windowResized(int w, int h) override;
  void dragEvent(ofDragInfo dragInfo) override;
  void gotMessage(ofMessage msg) override;

  LSystem lsystem;
  Turtle turtle;

  vector <Reveal> reveals;
  const int maxReveals = 8;
  ofPolyline bigLine;
  
};


