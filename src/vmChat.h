#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"


class vmChat : public vmVideoSource, ofBaseApp{
private:
	struct Message {
		int personID;
		string  message;
	};

	vector<Message> messages;
	vector<ofImage> portraitThumbs;
	int portraitSize;

	int currentPerson;
	int totalHeight, _totalHeight;

	ofTrueTypeFont messengerFont;
	ofFbo fbo;

	ofSoundPlayer msgArrivedSnd,
					keyPressedSnd;

	void addKeyToString(string &message, int key);
	void lineBreak(string &message);


public:
	vmChat();
	void draw(int x, int y, int w, int h);
	ofTexture* getTexture();
	void receiveKeyInput(int key);

	//--------------------------------------------------------------


};