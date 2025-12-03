#pragma once

#include "ofMain.h"

class Turtle {
public:
  void setup(float _length, float _angle);
  void render(string sentence);
  float length;
  float angle;


  ofPath getPath() { return path; } // Add getter for the path

  private:
  ofPath path; // Add path member
};
