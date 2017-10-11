#pragma once

#include "ofMain.h"
#include "ofxAvVideoPlayer.h"

class outputWindow : public ofBaseApp {

public:

	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofTexture outTexture;
};
