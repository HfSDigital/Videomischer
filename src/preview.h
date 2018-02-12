#pragma once

#include "ofMain.h"
#include "vmVideoSource.h"
#include "outputWindowApp.h"

#include "globals.h"

class preview
{
public:
	preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource);
	void setSize(ofVec2f size);
	void setPos(ofVec2f pos);
	void draw();
	void trimTitle();

	int inside(float _x, float _y);
	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);
	//ofEvent<int> clickedInside;

	//--------------------------------------------------------------
	shared_ptr<outputWindowApp> outputWindow; 
	shared_ptr<vmVideoSource> videoSource;
	ofVec2f size;
	ofVec2f pos;
	int isMouseOver;

	ofTrueTypeFont std_font;
	string titleTrimmed;

};