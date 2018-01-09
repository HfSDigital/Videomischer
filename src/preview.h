#pragma once
#include "ofMain.h"
#include "guiColors.h"

class preview : public ofBaseApp {

public:
	preview(int id, ofVec2f pos, ofVec2f size, int outDisplay);
	ofEvent<ofVec2f> clickedInside;			// this gives us the PreviewID 
	ofVec2f pos, size;
	bool isMouseOver = false;

	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);
	bool inside(float _x, float _y);

private:
	int outDisplay;
	int id;
};