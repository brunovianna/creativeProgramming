// in ofApp.cpp
#include "ofApp.h"

// CHANGE THIS IP to the address of the OTHER computer
const std::string REMOTE_IP = "192.168.1.50"; 

const int PORT = 9000; // We will use the same port for send/recv

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // 1. Setup Live Video
    camWidth = 640;
    camHeight = 480;
    grabber.setup(camWidth, camHeight);
    
    // 2. Load the YuNet Model via the FaceDetectorYN wrapper
    string modelPath;

    if (cv::getVersionMajor()>=4) {
        if (cv::getVersionMinor()<=6) {
            // opencv 4.6.0
            modelPath = ofToDataPath("face_detection_yunet_2022mar.onnx"); 
        } else {
            // opencv 4.9.0 and greater
            modelPath = ofToDataPath("face_detection_yunet_2023mar.onnx");

        }
    }

    
    //string modelPath = ofToDataPath("yunet.onnx");
    cv::Size inputSize = cv::Size(320, 320); // The size the network prefers
    float scoreThreshold = 0.6; // Confidence threshold
    float nmsThreshold = 0.3;   // Non-Maximum Suppression threshold
    int topK = 5000;            // Keep top 5000 detections before NMS

    // Call the static 'create' method to initialize the detector
    detector = cv::FaceDetectorYN::create(
        modelPath,
        "", // config file (not needed for this model)
        inputSize,
        scoreThreshold,
        nmsThreshold,
        topK
    );
    
    if (detector.empty()) {
        ofLogError() << "Failed to load YuNet model. Make sure 'face_detection_yunet_2023mar.onnx' is in bin/data/";
    } else {
        ofLogNotice() << "cv::FaceDetectorYN loaded successfully.";
    }

    // Listen on the port
    receiver.setup(PORT);
    // Send to the remote IP on the same port
    sender.setup(REMOTE_IP, PORT);





}

//--------------------------------------------------------------
void ofApp::update(){

// ---------------------------
    // 1. RECEIVE OSC DATA
    // ---------------------------
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // Protocol: Whenever we receive /frame/start, we clear the list 
        // because it means a new video frame is being sent.
        if(m.getAddress() == "/frame/start"){
            remoteFaces.clear();
        }
        else if(m.getAddress() == "/face/data"){
            RemoteFace rf;
            
            // Parse Rectangle (x, y, w, h)
            rf.bounds.x = m.getArgAsInt(0);
            rf.bounds.y = m.getArgAsInt(1);
            rf.bounds.width = m.getArgAsInt(2);
            rf.bounds.height = m.getArgAsInt(3);
            
            // Parse 5 Landmarks (10 args: x,y, x,y...)
            // Args 4 to 13
            for(int k = 4; k < 14; k += 2){
                float lx = m.getArgAsInt(k);
                float ly = m.getArgAsInt(k+1);
                rf.landmarks.push_back(ofPoint(lx, ly));
            }
            
            remoteFaces.push_back(rf);
        }
    }

    grabber.update();

    if (grabber.isFrameNew()) {
        detectedFaces.clear();
        faceFeatures.clear();

        colorImg.setFromPixels(grabber.getPixels());
        cv::Mat frame = colorImg.getCvMat();
        detector->setInputSize(cv::Size(frame.cols, frame.rows));

        cv::Mat faces;
        detector->detect(frame, faces);
        
        // --- Prepare OSC Frame Start Message ---
        ofxOscMessage mStart;
        mStart.setAddress("/frame/start");
        sender.sendMessage(mStart, false);
        
        if (faces.rows > 0) {
            for (int i = 0; i < faces.rows; i++) {
                
                // Extract Local Data
                int x = static_cast<int>(faces.at<float>(i, 0));
                int y = static_cast<int>(faces.at<float>(i, 1));
                int w = static_cast<int>(faces.at<float>(i, 2));
                int h = static_cast<int>(faces.at<float>(i, 3));
                
                detectedFaces.push_back(ofRectangle(x, y, w, h));

                // Create OSC Message for this face
                ofxOscMessage mFace;
                mFace.setAddress("/face/data");
                mFace.addIntArg(x);
                mFace.addIntArg(y);
                mFace.addIntArg(w);
                mFace.addIntArg(h);

                // Extract and Pack Landmarks
                for (int j=4; j<14; j+=2) {
                    int lx = static_cast<int>(faces.at<float>(i, j));
                    int ly = static_cast<int>(faces.at<float>(i, j+1));
                    
                    faceFeatures.push_back(ofPoint(lx,ly));
                    
                    // Add landmarks to OSC message
                    mFace.addIntArg(lx);
                    mFace.addIntArg(ly);
                }
                
                // Send this face
                sender.sendMessage(mFace, false);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255);
    grabber.draw(0, 0); // Draw the live video

    ofNoFill();
    ofSetLineWidth(2);
// ---------------------------
    // DRAW LOCAL FACES (RED)
    // ---------------------------
    ofSetColor(ofColor::red);
    for (auto& rect : detectedFaces) {
        ofDrawRectangle(rect);
    }
    for (auto& pt : faceFeatures) {
        ofDrawCircle(pt, 3);
    }

    // ---------------------------
    // DRAW REMOTE FACES (CYAN)
    // ---------------------------
    ofSetColor(ofColor::cyan);
    for (auto& rFace : remoteFaces) {
        ofDrawRectangle(rFace.bounds);
        
        for(auto& pt : rFace.landmarks){
            ofDrawCircle(pt, 3);
        }
        
        // Optional: Label them
        ofDrawBitmapString("Remote", rFace.bounds.x, rFace.bounds.y - 10);
    }

    // Draw info
    ofSetColor(ofColor::white);
    ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate(), 0), 20, 30);
    ofDrawBitmapString("Local Faces: " + ofToString(detectedFaces.size()), 20, 50);
    ofDrawBitmapString("Remote Faces: " + ofToString(remoteFaces.size()), 20, 70);
    ofDrawBitmapString("Sending to: " + REMOTE_IP, 20, 90);
}
