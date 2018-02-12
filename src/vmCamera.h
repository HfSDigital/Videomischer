#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"

#include "ofVideoGrabber.h"


class vmCamera : public vmVideoSource {

public:
	vmCamera(int deviceID);
	void update();
	void draw(int x, int y, int w, int h);
	void play();
	void stop();
	void setVolume(float v);

	//--------------------------------------------------------------

	ofTexture* getTexture();
	ofVideoGrabber videoGrabber;
};