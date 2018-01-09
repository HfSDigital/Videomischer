#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	ofSetVerticalSync(true);

	// Setup for Previews
	padding = 20;
	
	// Load default VideoStreams
	videoStreams.push_back(new videostream(0));													// open Webcam with DeviceID '0'
	videoStreams.push_back(new videostream("C:/Users/Puppe/Desktop/big_buck_bunny.mp4"));	// open Videofile 


	// add click-listener to preview-boxes
	for (int i = 0; i < videoStreams.size(); i++) {
		ofAddListener(videoStreams[i]->clickedInside, this, &ofApp::onMouseClickedInPreview);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(guiColors::background);

	// Update all VideoStreams
	for (int i = 0; i < videoStreams.size(); i++) {
		videoStreams[i]->update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Show Preview of all VideoStreams
	for (int i = 0; i < videoStreams.size(); i++) {
		videoStreams[i]->drawPreview(padding + i * (videoStreams[i]->getPreviewWidth() + padding), padding);
		videoStreams[i]->drawPreview(padding + i * (videoStreams[i]->getPreviewWidth() + padding), padding + 120);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == '1')	  	 outputWindow01->outTexture = videoStreams[0]->getTexture();
	else if (key == '2') outputWindow01->outTexture = videoStreams[1]->getTexture();

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

void ofApp::onMouseClickedInPreview(int& e) {
	cout << "clicked inside Preview ID: " << e << endl;
	outputWindow03->outTexture = videoStreams[e]->getTexture();
}
