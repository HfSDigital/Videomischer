#pragma once

#include "ofMain.h"
#include "ofxHomography.h"
#include "ofxJSON.h"

class ofApp;

class outputWindowApp : public ofBaseApp {

public:
	outputWindowApp();
	outputWindowApp(int id);
	void setTexture(ofTexture* _outTexture);
	void setup();
	void update();
	void draw();
	void keyPressed(ofKeyEventArgs& e);
	void keyReleased(ofKeyEventArgs& e);
	void exit();
	void windowResized(int w, int h);
	void updateHomography();
	ofxJSONElement getParameters();
	void setFullscreen();

	int inside(ofPoint mousePos);
	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);

	//--------------------------------------------------------------

	ofTexture *outTexture, *outTextureB;
	float fadeAB, fadeTime;
	int currentTexture;
	

	int videosourceID;
	static vector<int> idCounter;
	int id;
	bool isRunning;

	ofVec2f windowSize;
	ofVec2f windowPosition;
	bool isFullscreen;

	// Everything for the 4-Point-Homographic Mapping:
	ofPoint originalCorners[4];
	ofPoint distortedCorners[4];
	ofPoint distortedCornersScreen[4];
	ofPoint originalCornersScreen[4];
	ofMatrix4x4 homography;
	int clickedCorner;
	int cornerSize;

	uint64_t fadeCornerPointsTimer;
	uint64_t timeout{ 1000 };

	ofApp* _mainApp;

};