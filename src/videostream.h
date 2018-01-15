#pragma once

#include "ofMain.h"
#include "ofxAvVideoPlayer.h"
#include "guiColors.h"
#include "preview.h"


class videostream : public ofBaseApp
{
public:
	videostream();
	videostream(int devideID);
	videostream(string filename);
	~videostream();
	void update();
	void drawPreview();
	void addPreview(ofVec2f pos, int outDisplay, ofVec2f size = ofVec2f(160,100));
	ofTexture getTexture();

	int getWidth();
	int getHeight();
	int getPreviewWidth();
	int getPreviewHeight();
	//ofVec2f getPosition();
	//string getTitle();

	vector<preview*> previews;
	void play();

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
	ofSoundStream soundStream;
	void audioOut(float * output, int bufferSize, int nChannels);
	ofImage blackimage;

	ofFbo previewFbo;
	bool previewIsInitialized;
	enum {
		videoFile,
		webcam,
		empty
	} streamtype;
};
