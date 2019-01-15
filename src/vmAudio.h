#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"



class vmAudio : public vmVideoSource , public ofBaseApp {
private:
	ofFbo fbo;
	ofSoundPlayer audio;

public:
	vmAudio(string filename);
	void update();
	void draw(int x, int y, int w, int h);
	void play();
	void stop();
	void setVolume(float v);
	void setLoop(bool l);
	void audioOut(float * output, int bufferSize, int nChannels);

	//--------------------------------------------------------------

	ofTexture* getTexture();
	//ofSoundStream soundStream;
	string filename;


};