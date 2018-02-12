#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"


class vmPicture : public vmVideoSource {

public:
	vmPicture(string filename);
	void update();
	void draw(int x, int y, int w, int h);
	void play();
	void stop();
	void setVolume(float v);
	void audioOut(float * output, int bufferSize, int nChannels);

	//--------------------------------------------------------------

	ofTexture* getTexture();
	ofImage picture;

};