#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	camWidth = 640;
	camHeight = 480;
	
	// vector<ofVideoDevice> devices = videoGrabber.listDevices();

	//for (size_t i = 0; i < devices.size(); i++) {
	//	if (devices[i].bAvailable) {
	//		//log the device
	//		ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
	//	}
	//	else {
	//		//log the device and note it as unavailable
	//		ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
	//	}
	//}
	

	videoGrabber.setDeviceID(0);
	videoGrabber.setDesiredFrameRate(60);
	videoGrabber.initGrabber(camWidth, camHeight);

	// Der ofxAvCodec VideoPlayer (https://github.com/kritzikratzi/ofxAvCodec)
	videoPlayer.load("C:/Users/greenOne/Desktop/big_buck_bunny.mp4");

	ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100, 100, 100);
	videoGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetHexColor(0xffffff);
	videoGrabber.draw(20, 20);
	
	videoPlayer.update();  // it's weird, but ... do this in draw(), not in update! 
	videoPlayer.draw(680, 20); // draw at 10,10
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
