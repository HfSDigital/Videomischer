#pragma once
#include "ofMain.h"


class vmVideoSource {

public:
	vmVideoSource();
	~vmVideoSource();
	void printName();

	//--------------------------------------------------------------

	virtual void draw(int x, int y, int w, int h) = 0;
	virtual void update() = 0;
	virtual ofTexture* getTexture() = 0;
	virtual void play() = 0;
	virtual void stop() = 0;
	virtual void setVolume(float v) = 0;

	//--------------------------------------------------------------

	string title;
	static int idCounter;
	int id;
};