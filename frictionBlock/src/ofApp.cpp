#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("OF Friction and Gravity Demo (Simple)");
    ofSetFrameRate(60); // Set a stable frame rate for consistent simulation

    // Initialize position near the ground
    groundLevel = ofGetHeight() * 0.75f;
    position.set(ofGetWidth() / 2, groundLevel - (blockSize / 2));
    velocity.set(2, 0);
    acceleration.set(0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // --- STEP 1: Reset acceleration ---
    acceleration.set(0, 0);

    // --- STEP 2: Apply Forces ---

    // 2a. Apply Gravity
    applyForce(GRAVITY * mass);

    // 2b. Apply Mouse Force (if held)
    if (isMousePressed) {
        ofVec2f direction = mousePos - position;
        float distance = direction.length();

        // Force is proportional to distance
        appliedMouseForce = direction.getNormalized() * (distance * MOUSE_FORCE_SCALE);
        applyForce(appliedMouseForce);
    } else {
        appliedMouseForce.set(0, 0);
    }

    velocity += acceleration; // v = v + a * (1)

    // --- STEP 4: Handle Ground Collision and Friction ---

    // Block is on the ground if its center's Y position is >= the ground level minus half the block height.
    if (position.y >= groundLevel - (blockSize / 2)) {

        // a. Clamp Position and stop downward velocity
        position.y = groundLevel - (blockSize / 2);
        if (velocity.y > 0) velocity.y = 0;

        // b. Calculate Normal Force (required for friction)
        // Normal force is the counter-force to all vertical downward forces.
        // If the net vertical force is upward (block lifts off), Normal Force is 0.
        float totalDownwardForce = (GRAVITY.y * mass) - appliedMouseForce.y;
        float normalForceMagnitude = max(0.0f, totalDownwardForce);

        // c. Apply Kinetic Friction
        if (normalForceMagnitude > 0 && abs(velocity.x) > 0.001f) {
            ofVec2f frictionForce;

            // Friction magnitude: F_f = mu_k * F_N
            float frictionMagnitude = MU_KINETIC * normalForceMagnitude;

            // Friction direction: Opposite to the horizontal velocity
            frictionForce.x = -velocity.getNormalized().x * frictionMagnitude;

            // Apply friction force
            applyForce(frictionForce);
            
            // Re-integrate with the new (friction-adjusted) acceleration
            velocity += acceleration;
        }

        // d. Dampen horizontal velocity to prevent infinite sliding
        if (abs(velocity.x) < 0.1f) {
            velocity.x = 0;
        }
    }

    // --- STEP 3: Update Physics (Simple Euler Integration with Delta Time = 1) ---

    position += velocity;     // p = p + v * (1)

    // --- STEP 5: Handle horizontal boundaries ---
    if (position.x < blockSize / 2 || position.x > ofGetWidth() - blockSize / 2) {
        velocity.x *= -0.8f; // Bounce with energy loss
        if (position.x < blockSize / 2) position.x = blockSize / 2 + 5;
        if (position.x > ofGetWidth() - blockSize / 2) position.x = ofGetWidth() - blockSize / 2 - 5;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255); // White background

    // --- Draw the Surface (Ground) ---
    ofSetColor(150, 75, 0); // Brown
    ofDrawRectangle(0, groundLevel, ofGetWidth(), ofGetHeight() - groundLevel);

    // --- Draw the Block ---
    ofSetColor(200, 0, 0); // Red block
    ofDrawRectangle(position.x - blockSize / 2, position.y - blockSize / 2, blockSize, blockSize);

    // --- Draw Force Arrow (Mouse Force) ---
    if (isMousePressed) {
        // The force arrow shows the *actual* force vector, scaled down for visibility
        ofVec2f forceEnd = position + appliedMouseForce * 1.5f;

        drawForceArrow(position, forceEnd, ofColor(0, 0, 200));

        // Draw a line from the block to the mouse for context
        ofSetColor(0, 0, 200, 100);
        ofDrawLine(position, mousePos);
    }

    // --- Draw Debug Info ---
    ofSetColor(0);
    string debugInfo;
    debugInfo += "Hold mouse button to apply force.\n";
    debugInfo += "Force is proportional to distance from mouse.\n";
    debugInfo += "Velocity: " + ofToString(velocity.x, 2) + ", " + ofToString(velocity.y, 2) + "\n";
    debugInfo += "Acceleration (a = F/m): " + ofToString(acceleration.x, 2) + ", " + ofToString(acceleration.y, 2) + "\n";
    debugInfo += "On Ground: " + ofToString(position.y >= groundLevel - (blockSize / 2)) + "\n";
    ofDrawBitmapString(debugInfo, 10, 20);
}

//--------------------------------------------------------------
void ofApp::applyForce(ofVec2f force) {
    // F = ma -> a = F/m. Since mass is 1, a = F.
    acceleration += force / mass;
}

//--------------------------------------------------------------
void ofApp::drawForceArrow(ofVec2f start, ofVec2f end, ofColor color) {
    ofSetColor(color);
    ofSetLineWidth(2);
    ofDrawLine(start, end);

    // Draw the arrowhead
    ofVec2f direction = end - start;
    float headSize = 10.0f;

    // Rotate the arrow
    float angle = atan2(direction.y, direction.x);

    ofPushMatrix();
    ofTranslate(end);
    ofRotateDeg(ofRadToDeg(angle));

    // Draw triangle for the arrowhead
    ofDrawTriangle(
        0, 0,
        -headSize, headSize / 2,
        -headSize, -headSize / 2
    );

    ofPopMatrix();
    ofSetLineWidth(1); // Reset line width
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    isMousePressed = true;
    mousePos.set(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    mousePos.set(x, y);
}

// Dummy/Unused functions (required by OF structure)
void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::dragEvent(ofDragInfo dragInfo){}
void ofApp::gotMessage(ofMessage msg){}