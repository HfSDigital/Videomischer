#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"
#include "outputWindowApp.h"

#include "globals.h"

class preview
{
public:
	preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource, shared_ptr<ofTrueTypeFont> std_font);
	~preview();
	void setSize(ofVec2f size);
	void setPos(ofVec2f pos);
	void draw();
	void trimTitle();

	int inside(float _x, float _y, bool hasClicked = false);
	
	//ofEvent<int> clickedInside;

	//--------------------------------------------------------------
	shared_ptr<outputWindowApp> outputWindow; 
	shared_ptr<vmVideoSource> videoSource;
	ofVec2f size;
	ofVec2f pos;
	int isMouseOver;

	shared_ptr<ofTrueTypeFont> std_font;
	string titleTrimmed;

};