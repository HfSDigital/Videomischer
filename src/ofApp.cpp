#include <Windows.h>
#include <iostream>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// read data folder and get all files
	
	ofSetVerticalSync(true);

	// one empty stream as 'simple black'
	videoStreams.push_back(new videostream());

	// Load default VideoStreams 
	int camcount = tmpVideoGrabber.listDevices().size();
	for (int i = 0; i < camcount; i++) {
		try {
			videoStreams.push_back(new videostream(i));						// open Webcam with DeviceID '0'
		}
		catch (int e) {
			cout << "UNABLE TO OPEN CAPTURE DEVICE: " << e << endl;
		}
	}

	// Load Videofiles from data - Folder
	ofDirectory dir("video");
	vector<ofFile> videofiles = dir.getFiles();
	for (int i = 0; i < videofiles.size(); i++) {
		cout << videofiles[i].getAbsolutePath() << endl;
		videoStreams.push_back(new videostream(videofiles[i].getAbsolutePath()));	// open Videofile 
	}

	// Setup for Previews
	padding = 20;
	float pwidth;
	if (videoStreams.size() > 4) {
		pwidth = (ofGetWindowWidth() - padding * (videoStreams.size() + 1)) / videoStreams.size();
	}
	else {
		pwidth = (ofGetWindowWidth() - padding * (5 + 1)) / 5;
	}
	cout << "pwidth :" << pwidth << endl;
	previewSize = ofVec2f(pwidth, pwidth/16.0f*9.0f);

	// add previews with click-listener for each videostream x each outputWindow
	for (int i = 0; i < videoStreams.size(); i++) {
		for (int j = 0; j < outputWindows.size(); j++) {
			videoStreams[i]->addPreview(ofVec2f(padding + i * (previewSize.x + padding),
												padding*3 + j * (previewSize.y + padding*5)), j, previewSize);
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
	ofPushStyle();
	ofBackground(33);
	ofFill();
	ofSetColor(99);
	for (int i = 0; i < outputWindows.size(); i++) {
		ofRect(0, padding + i * previewSize.y + padding * i * 5,	ofGetWindowWidth(), previewSize.y + padding * 4);
	}
	ofNoFill();
	ofSetColor(255);
	for (int i = 0; i < outputWindows.size(); i++) {
		string s = "Display " + to_string(i);
		ofDrawBitmapString(s, padding, padding + i * previewSize.y + padding * i * 5 + padding);
	}
	ofPopStyle();

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
	videoStreams[(int)e.x]->play();
	outputWindows[(int)e.y]->outTexture = videoStreams[(int)e.x]->getTexture();
}
