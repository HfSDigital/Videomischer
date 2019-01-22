#pragma once
#include "ofMain.h"


class vmVideoSource {

public:
	vmVideoSource();
	~vmVideoSource();
	void printName();

	//--------------------------------------------------------------

	virtual void draw(int x, int y, int w, int h);
	virtual void update();
	virtual ofTexture* getTexture();
	virtual void play();
	virtual void pause();
	virtual void stop();
	virtual void setVolume(float v);
	virtual void setLoop(bool l);
	virtual void receiveKeyInput(int key);

	//--------------------------------------------------------------

	string title;
	static int idCounter;
	int id;
	bool playInBackground = false;
	bool bMute = false;
	bool bLoop = false;

};