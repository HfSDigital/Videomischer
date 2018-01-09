#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	ofSetVerticalSync(true);

	// Setup for Previews
	padding = 20;

	// Load default VideoStreams
	videoStreams.push_back(new videostream(0));													// open Webcam with DeviceID '0'
	videoStreams.push_back(new videostream("C:/Users/Puppe/Desktop/big_buck_bunny.mp4"));	// open Videofile 


	// add previews with click-listener for each videostream x each outputWindow
	for (int i = 0; i < videoStreams.size(); i++) {
		for (int j = 0; j < outputWindows.size(); j++) {
			videoStreams[i]->addPreview(ofVec2f(padding + i * (videoStreams[i]->getPreviewWidth()  + padding), 
												padding + j * (videoStreams[i]->getPreviewHeight() + padding)), j);
			ofAddListener(videoStreams[i]->previews[j]->clickedInside, this, &ofApp::onMouseClickedInPreview);
		}
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
		videoStreams[i]->drawPreview();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	//if (key == '1')	  	 outputWindow01->outTexture = videoStreams[0]->getTexture();
	//else if (key == '2') outputWindow01->outTexture = videoStreams[1]->getTexture();

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

void ofApp::onMouseClickedInPreview(ofVec2f& e) {
	cout << "clicked inside Preview ID: " << e.x << "for output Display " << e.y << endl;
	outputWindows[(int)e.y]->outTexture = videoStreams[(int)e.x]->getTexture();
}
