#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"
#include "outputWindowApp.h"
//#include "gui.h"
#include "globals.h"


class preview
{
private:

	struct btn {
		int x, y, r;
		string name;
		ofColor color;
		bool isMouseOver;
		
	};


public:
	//static int previewID;

	preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource, shared_ptr<ofTrueTypeFont> std_font);
	~preview();
	void setSize(ofVec2f size);
	void setPos(ofVec2f pos);
	void draw();
	void showVideo();
	void trimTitle();
	void inside(float _x, float _y, bool hasClicked = false);
	
	//--------------------------------------------------------------
	
	shared_ptr<outputWindowApp> outputWindow; 
	shared_ptr<vmVideoSource> videoSource;
	ofVec2f size;
	ofVec2f pos;
	int isMouseOver;

	int keyboardShortcut;
	bool waitForKey;
	//bool bMute, bLoop;

	vector<btn> btns;

	shared_ptr<ofTrueTypeFont> std_font;
	string titleTrimmed;

};