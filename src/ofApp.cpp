#include <Windows.h>
#include <iostream>
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// read data folder and get all files
	ofDirectory dir("video");
	vector<ofFile> videofiles;
	videofiles = dir.getFiles();
	for (int i = 0; i < videofiles.size(); i++) {
		cout << videofiles[i].getAbsolutePath() << endl;
	}
	
	ofSetVerticalSync(true);

	// Setup for Previews
	padding = 20;


	// one empty stream as 'simple black'
	videoStreams.push_back(new videostream());

	// Load default VideoStreams and Videofiles from data-Folder
	videoStreams.push_back(new videostream(0));													// open Webcam with DeviceID '0'
	for (int i = 0; i < videofiles.size(); i++) {
		videoStreams.push_back(new videostream(videofiles[i].getAbsolutePath()));	// open Videofile 
	}


	// add previews with click-listener for each videostream x each outputWindow
	for (int i = 0; i < videoStreams.size(); i++) {
		for (int j = 0; j < outputWindows.size(); j++) {
			videoStreams[i]->addPreview(ofVec2f(padding*2 + i * (videoStreams[i]->getPreviewWidth()  + padding), 
												padding*3 + j * (videoStreams[i]->getPreviewHeight() + padding*5)), j);
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
	ofBackground(55);
	ofFill();
	ofSetColor(77);
	ofRect(padding, padding, ofGetWindowWidth() - padding * 2, 100 + padding * 4);

	ofRect(padding, padding + 100 + padding * 5, ofGetWindowWidth() - padding * 2, 100 + padding * 4);

	ofRect(padding, padding + 200 + padding * 10, ofGetWindowWidth() - padding * 2, 100 + padding * 4);
	ofNoFill();
	ofSetColor(255);
	ofDrawBitmapString("Display 1", padding * 2, padding * 2);
	ofDrawBitmapString("Display 2", padding * 2, padding + 100 + padding * 6);
	ofDrawBitmapString("Display 3", padding * 2, padding + 200 + padding * 11);
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
	outputWindows[(int)e.y]->outTexture = videoStreams[(int)e.x]->getTexture();
	videoStreams[(int)e.x]->play();
}
