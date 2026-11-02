#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	string apiKey = "YOUR_GEMINI_API_KEY";

	// 1. Text Prompt
	string reply = getGeminiText("Write a 1-sentence poetic description of generative design.", apiKey);
	ofLogNotice() << "Gemini Reply: " << reply;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
std::string ofApp::getGeminiText(const std::string & prompt, const std::string & apiKey) {
	std::string url = "https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=" + apiKey;

	ofHttpRequest request;
	request.url = url;
	request.method = ofHttpRequest::POST;
	request.headers["Content-Type"] = "application/json";

	ofJson reqJson;
	reqJson["contents"][0]["parts"][0]["text"] = prompt;
	request.body = reqJson.dump();

	ofURLFileLoader loader;
	ofHttpResponse response = loader.handleRequest(request);

	if (response.status == 200) {
		try {
			ofJson resJson = ofJson::parse(response.data.getText());
			return resJson["candidates"][0]["content"]["parts"][0]["text"].get<std::string>();
		} catch (const std::exception & e) {
			ofLogError("GeminiAPI") << "JSON parse error: " << e.what();
		}
	} else {
		ofLogError("GeminiAPI") << "HTTP Error " << response.status << ": " << response.error;
	}

	return "";
}
