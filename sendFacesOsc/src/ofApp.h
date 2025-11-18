// in ofApp.h
#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofVideoGrabber.h"
#include "ofxOsc.h"

// include the dnn and objdetect headers
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"


// A structure to hold data for faces received from the other computer
struct RemoteFace {
    ofRectangle bounds;
    std::vector<ofPoint> landmarks;
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    ofVideoGrabber grabber;
    int camWidth;
    int camHeight;
    

    //
    // We use a Ptr (a smart pointer) to hold the detector
    cv::Ptr<cv::FaceDetectorYN> detector;
    //
    // -----------------------------
    //
    
    // Vector to store the final, processed face rectangles
    std::vector<ofRectangle> detectedFaces;
    std::vector<ofPoint> faceFeatures;

	ofxCvColorImage colorImg;


    // OSC Networking
    ofxOscSender sender;
    ofxOscReceiver receiver;
    
    // Store faces received from the LAN client here
    std::vector<RemoteFace> remoteFaces;

};