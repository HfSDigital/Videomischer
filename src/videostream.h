#pragma once

#include "ofMain.h"
#include "ofxAvVideoPlayer.h"
#include "guiColors.h"
#include "preview.h"


class videostream : public ofBaseApp
{
public:
	videostream(int devideID);
	videostream(string filename);
	~videostream();
	void update();
	void drawPreview();
	void addPreview(ofVec2f pos, int outDisplay);
	ofTexture getTexture();

	int getWidth();
	int getHeight();
	int getPreviewWidth();
	int getPreviewHeight();
	//ofVec2f getPosition();
	//string getTitle();

	vector<preview*> previews;



	

private:
	void initPreview();

	static int previewIDCounter;
	int previewID;
	//string title;
	int width;
	int height;
	int previewWidth;
	int previewHeight;

	ofVideoGrabber videoGrabber;
	ofxAvVideoPlayer videoPlayer;
	

	ofFbo previewFbo;

	enum {
		videoFile,
		webcam
	} streamtype;
};
