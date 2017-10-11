#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// of-interne VideoGrabber
	camWidth = 640;
	camHeight = 480;
	videoGrabber.setDeviceID(0);
	videoGrabber.setDesiredFrameRate(60);
	videoGrabber.initGrabber(camWidth, camHeight);

	// ofxAvCodec VideoPlayer (https://github.com/kritzikratzi/ofxAvCodec)
	videoPlayer.load("C:/Users/greenOne/Desktop/big_buck_bunny.mp4");

	ofSetVerticalSync(true);

	// Setup für Previews
	padding = 20;
	maxPreviews = 2;
	for (int i = 0; i < maxPreviews; i++) {
		previews.push_back(ofFbo());
		previews[i].allocate(160, 100, GL_RGBA, ofFbo::maxSamples());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	ofBackground(100, 100, 100);
	videoGrabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){


	// Preview Thumbnails befüllen
	previews[0].begin();
		videoPlayer.update();  // it's weird, but ... do this in draw(), not in update! 
		videoPlayer.draw(0, 0, previews[0].getWidth(), previews[0].getHeight());
	previews[0].end();
	
	previews[1].begin();
		videoGrabber.draw(0, 0, previews[1].getWidth(), previews[1].getHeight());
	previews[1].end();


	// Alle Previews anzeigen
	for (int i = 0; i < previews.size(); i++) {
		previews[i].draw(padding + i * (previews[i].getWidth() + padding), padding);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == '1')
	{ 
		outputApp->outTexture = videoPlayer.getTexture();
		cout << "Video 1" << endl; 
	} 

	else if (key == '2')
	{
		outputApp->outTexture = videoGrabber.getTexture();
		cout << "Video 2" << endl;
	}

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
