#pragma once

#include "ofMain.h"
#include "ofxAvVideoPlayer.h"
#include "guiColors.h"


class videostream : public ofBaseApp
{
public:
	videostream(int devideID);
	videostream(string filename);
	~videostream();
	void update();
	void drawPreview(int x, int y);
	ofTexture getTexture();

	int getWidth();
	int getHeight();
	int getPreviewWidth();
	int getPreviewHeight();
	ofVec2f getPosition();
	string getTitle();

	ofEvent<int> clickedInside;			// this gives us the PreviewID 


	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);
	bool inside(float _x, float _y);

	

private:
	void initPreview();
	static int previewIDCounter;
	int previewID;
	int x, y;
	int width;
	int height;
	int previewWidth;
	int previewHeight;
	string title;
	
	bool isMouseOver = false;


	ofVideoGrabber videoGrabber;
	ofxAvVideoPlayer videoPlayer;

	ofFbo previewFbo;

	enum {
		videoFile,
		webcam
	} streamtype;
};
