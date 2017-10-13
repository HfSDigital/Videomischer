#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


	ofSetVerticalSync(true);

	// Setup for Previews
	padding = 20;
	
	// Load default VideoStreams
	videoStreams.push_back(new videostream(0));													// open Webcam with DeviceID '0'
	videoStreams.push_back(new videostream("C:/Users/greenOne/Desktop/big_buck_bunny.mp4"));	// open Videofile 
	


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
	// Draw the drag-drop line
	if (drawDragLine) {
		ofPushStyle();
		ofSetColor(guiColors::border);
		ofSetLineWidth(1.0f);
		ofDrawLine(videoStreams[draggedPreviewID]->getPosition().x + videoStreams[draggedPreviewID]->getPreviewWidth()/2, videoStreams[draggedPreviewID]->getPosition().y + videoStreams[draggedPreviewID]->getPreviewHeight(), mouseX, mouseY);
		ofPopStyle();
	}

	// Show Preview of all VideoStreams
	for (int i = 0; i < videoStreams.size(); i++) {
		videoStreams[i]->drawPreview(padding + i * (videoStreams[i]->getPreviewWidth() + padding), padding);
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == '1')	  	 outputApp->outTexture = videoStreams[0]->getTexture();
	else if (key == '2') outputApp->outTexture = videoStreams[1]->getTexture();

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	cout << "ofApp dragging ID " << draggedPreviewID << " to: " << x << ", " << y << endl;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	drawDragLine = false;
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
	draggedPreviewID = e; 
	drawDragLine = true;
}
