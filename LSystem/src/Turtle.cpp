#include "Turtle.h"

void Turtle::setup(float _length, float _angle) {
  length = _length;
  angle = _angle;
}

void Turtle::render(string sentence) {

    // Clear the previous path
  path.clear();
  
  // Set path properties
  path.setStrokeColor(ofColor(0));
  path.setStrokeWidth(1);
  path.setFilled(false);
  
  // Start position
  ofPoint currentPos(0, 0);
  float currentAngle = -HALF_PI; // Start pointing up (like original)
  
  // Stack for saving states (for branches)
  vector<pair<ofPoint, float>> stateStack;
  
  // Begin the path at the starting position
  path.moveTo(currentPos);

  for (int i = 0; i < sentence.size(); ++i) {
    char c = sentence[i];
    if ((c == 'F' )||(c=='G')) {
     // Calculate new position based on current angle
      ofPoint newPos = currentPos + ofPoint(
        length * cos(currentAngle),
        length * sin(currentAngle)
      );
      
      // Draw line to new position
      path.lineTo(newPos);
      
      // Update current position
      currentPos = newPos;
    } else if (c == '+') {
      currentAngle += angle;
    } else if (c == '-') {
      currentAngle -= angle;
    } else if (c == '[') {
      // Save current state to stack
      stateStack.push_back(std::make_pair(currentPos, currentAngle));
      // Start a new subpath at current position
      path.moveTo(currentPos);
    } else if (c == ']') {
      // Restore previous state from stack
      if (!stateStack.empty()) {
        auto savedState = stateStack.back();
        stateStack.pop_back();
        currentPos = savedState.first;
        currentAngle = savedState.second;
        // Move to the restored position without drawing
        path.moveTo(currentPos);
      }
    }
    // if (c == 'F' || c == 'G') {
    //   ofDrawLine(0, 0, 0, -length);
    //   ofTranslate(0, -length);
    // } else if (c == '+') {
    //   ofRotateRad(angle);
    // } else if (c == '-') {
    //   ofRotateRad(-angle);
    // } else if (c == '[') {
    //   ofPushMatrix();
    // } else if (c == ']') {
    //   ofPopMatrix();
    // }
  }
};
