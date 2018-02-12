#pragma once

#include "ofMain.h"


class outputWindowApp : public ofBaseApp {

public:
	outputWindowApp();
	void setTexture(ofTexture* _outTexture);
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	//--------------------------------------------------------------

	ofTexture*  outTexture;
	static int idCounter;
	int id;
};