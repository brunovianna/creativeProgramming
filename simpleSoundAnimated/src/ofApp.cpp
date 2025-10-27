#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetBackgroundColor(20, 20, 20);
	ofSetFrameRate(60);
	ofEnableDepthTest();


	// NOTE: Replace "beat.mp3" with your file name and ensure it's in bin/data/
	if (!player.load(ofToDataPath("beat.wav", true),false)) {
		ofLogFatalError("ofApp::setup") << "Failed to load sound file!";
	}




		//----- Sound stream setup begin -------.
	// the sound stream is in charge of dealing with your computers audio device.
	// lets print to the console the sound devices that can output sound.
	//ofxSoundUtils::printOutputSoundDevices();

	//auto outDevices = ofxSoundUtils::getOutputSoundDevices();

	// IMPORTANT!!!
	// The following line of code is where you set which audio interface to use.
	// the index is the number printed in the console inside [ ] before the interface name
	// You can use a different input and output device.

	//int outDeviceIndex = 2;

	//cout << "device 2" << ofxSoundUtils::getSoundDeviceString(outDevices[outDeviceIndex], false, true) << endl;


	ofSoundStreamSettings soundSettings;
	soundSettings.numInputChannels = 0;
	soundSettings.numOutputChannels = 2;
	soundSettings.sampleRate = player.getSoundFile().getSampleRate();
	soundSettings.bufferSize = 256;
	soundSettings.numBuffers = 1;

	stream.setup(soundSettings);

	stream.setOutput(output);

	player.connectTo(output);


	player.setLoop(true);
	player.play();


	cam.setPosition(0, 0, 500);
}

//--------------------------------------------------------------
void ofApp::update() {

	auto & buf = player.getBuffer();
	size_t numFrames = buf.getNumFrames();
	if (numFrames == 0) return;

	// normalized position (0.0 to 1.0)
	float pos = player.getPosition();
	// current frame index
	size_t frameIndex = std::min((size_t)(pos * (numFrames - 1) + 0.5f), numFrames - 1);

	//  RMS (in frames). Adjust window size as needed
	const size_t windowFrames = 512;
	size_t start = (frameIndex > windowFrames / 2) ? frameIndex - windowFrames / 2 : 0;
	size_t end = std::min(start + windowFrames, numFrames);

	size_t channels = buf.getNumChannels();
	double sumSq = 0.0;
	size_t sampleCount = 0;

	for (size_t f = start; f < end; ++f) {
		for (size_t c = 0; c < channels; ++c) {
			float s = buf.getSample(f, c);
			sumSq += double(s) * double(s);
			++sampleCount;
		}
	}

	//calculate rms
	volume = sampleCount ? float(sqrt(sumSq / sampleCount)) : 0.0f;



}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();

	// Calculate the sphere's vertical position
	// The louder the sound (higher smoothedVolume), the higher the sphere moves up (in 3D, positive Y is usually up).
	// We multiply smoothedVolume by the max movement.
	//float sphereY = sphereBaseY + (smoothedVolume * maxSphereMovement);

	// Draw the sphere
	ofSetColor(255, 100, 100);
	ofDrawSphere(-80, volume * maxSphereMovement, 0, 50);

	// draw smoothed sphere
	ofSetColor(100, 255, 100);
	 smoothedVolume = ofLerp(smoothedVolume, volume, volumeSmoothRate);
	smoothedVolume = ofClamp(smoothedVolume, 0.0f, 1.0f);
	 ofDrawSphere(80, smoothedVolume * maxSphereMovement, 0, 50);


	// Draw a "floor" for context
	ofSetColor(50);
	ofDrawBox(0, sphereBaseY, 0, 300, 1, 300);

	cam.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == ' ') {
		//player.togglePlayPause();
	}
}

// (Keep the remaining empty event handlers from the original file)
