#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"

#include "ofxAvVideoPlayer.h"


class vmPlayer : public vmVideoSource , public ofBaseApp {

public:
	vmPlayer(string filename);
	void update();
	void draw(int x, int y, int w, int h);
	void play();
	void pause();
	void stop();
	void setVolume(float v);
	void setLoop(bool l);
	void audioOut(float * output, int bufferSize, int nChannels);

	//--------------------------------------------------------------

	ofTexture* getTexture();
	ofSoundStream soundStream;
	ofxAvVideoPlayer videoPlayer;
	string filename;


};