// in ofApp.cpp
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);

    camWidth = 640;
    camHeight = 480;
    grabber.setup(camWidth, camHeight);
    colorImg.allocate(camWidth, camHeight);

    // 1. Set model parameters
    inputSize = cv::Size(304, 304); 
    confidenceThreshold = 0.5;

    // 2. Load the Caffe model
    string protoPath = ofToDataPath("openpose_pose_mpi.prototxt");
    string modelPath = ofToDataPath("pose_iter_160000.caffemodel");

    net = cv::dnn::readNetFromCaffe(protoPath, modelPath);

    if (net.empty()) {
        ofLogError() << "Failed to load OpenPose model. Check your bin/data/ folder.";
    } else {
        ofLogNotice() << "OpenPose model loaded successfully.";
    }
    

// This will only work if your OpenCV was built with CUDA support
        // It's safe to try, but may print an error if not supported.
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

    // Initialize our keypoints vector
    detectedKeypoints.resize(numKeypoints, ofPoint(0, 0, 0));

    frameCounter = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    grabber.update();

    // Only run if the frame is new AND the network is loaded
    if (!grabber.isFrameNew() || net.empty() || frameCounter % 3 != 0) {
        return;
    }

    // 1. Get our frame
    colorImg.setFromPixels(grabber.getPixels());
    cv::Mat frame = colorImg.getCvMat();

    // 2. Create the "blob" (the network input)
    // We scale pixels to 0-1 (1.0 / 255.0)
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0 / 255.0, inputSize, cv::Scalar(0, 0, 0), false, false);

    // 3. Set input and run the network
    net.setInput(blob);
    cv::Mat output = net.forward();

    //
    // --- 4. PARSE THE OUTPUT (The Hard Part) ---
    //
    
    // The output is a 4D matrix (blob):
    // [1, numKeypoints, heatmap_height, heatmap_width]
    
    int H = output.size[2]; // Heatmap height (e.g., 46)
    int W = output.size[3]; // Heatmap width (e.g., 46)

    // Calculate scaling factors to map heatmap points back to the camera image
    float scaleX = (float)camWidth / W;
    float scaleY = (float)camHeight / H;

    // Clear old points
    detectedKeypoints.clear();

    // Loop through all 15 keypoints
    for (int i = 0; i < numKeypoints; i++) {
        
        // Get the heatmap for this keypoint
        cv::Mat heatMap(H, W, CV_32F, output.ptr(0, i));

        // Find the (x, y) location of the highest confidence
        cv::Point maxLoc;
        double maxVal;
        cv::minMaxLoc(heatMap, NULL, &maxVal, NULL, &maxLoc);

        // If the confidence is high enough...
        if (maxVal > confidenceThreshold) {
            // ...scale the point from heatmap (46x46) to camera (640x480)
            float x = maxLoc.x * scaleX;
            float y = maxLoc.y * scaleY;
            detectedKeypoints.push_back(ofPoint(x, y));
        } else {
            // ...otherwise, add a "null" point
            detectedKeypoints.push_back(ofPoint(0, 0)); // (0,0) means not found
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    grabber.draw(0, 0);

    if (detectedKeypoints.empty()) {
        return;
    }

    // --- Draw the Skeleton ---

    // 1. Draw the "bones" (lines)
    ofSetColor(ofColor::green);
    ofSetLineWidth(3);

    for (int i = 0; i < 14; i++) { // Loop through all 14 pairs
        int idxA = MPII_PAIRS[i][0];
        int idxB = MPII_PAIRS[i][1];

        ofPoint pointA = detectedKeypoints[idxA];
        ofPoint pointB = detectedKeypoints[idxB];

        // Only draw the line if BOTH points were found (not 0,0)
        if (pointA.x != 0 && pointA.y != 0 && pointB.x != 0 && pointB.y != 0) {
            ofDrawLine(pointA, pointB);
        }
    }

    // 2. Draw the "joints" (circles)
    ofSetColor(ofColor::red);
    ofFill();
    for (int i = 0; i < numKeypoints; i++) {
        ofPoint p = detectedKeypoints[i];
        // Only draw if the point was found
        if (p.x != 0 && p.y != 0) {
            ofDrawCircle(p, 6);
        }
    }
    
    // --- Draw Info ---
    ofSetColor(ofColor::white);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 20, 30);
    ofDrawBitmapString("Model: OpenPose (MPII)", 20, 50);
}