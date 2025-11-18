// in ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofVideoGrabber.h"

#include "opencv2/dnn.hpp"
#include "opencv2/imgproc.hpp"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber grabber;
    int camWidth;
    int camHeight;
    ofxCvColorImage colorImg; // Our bridge to cv::Mat

    // 1. The DNN network
    cv::dnn::Net net;
    cv::Size inputSize;
    float confidenceThreshold;

    // 2. We'll store the detected points here
    // This model (MPII) has 15 keypoints
    std::vector<ofPoint> detectedKeypoints;
    const int numKeypoints = 15;

    // 3. Define the "bones"
    // These are pairs of keypoint indices to draw lines between
    // (e.g., [0, 1] is "Head" to "Neck")
    const int MPII_PAIRS[14][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 4},   // Right Arm
        {1, 5}, {5, 6}, {6, 7},           // Left Arm
        {1, 14}, {14, 8}, {8, 9}, {9, 10}, // Right Leg
        {14, 11}, {11, 12}, {12, 13}      // Left Leg
    };
    
    // Keypoint names (for reference)
    // 0: Head, 1: Neck, 2: RShoulder, 3: RElbow, 4: RWrist,
    // 5: LShoulder, 6: LElbow, 7: LWrist, 8: RHip, 9: RKnee,
    // 10: RAnkle, 11: LHip, 12: LKnee, 13: LAnkle, 14: Chest


	int frameCounter;
};