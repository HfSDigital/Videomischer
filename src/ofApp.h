#pragma once

#include "ofMain.h"

#include "IPVideoGrabber.h"
#include "ofxAvVideoPlayer.h"

#include "globals.h"

#include "vmVideoSource.h"
#include "outputWindowApp.h"
#include "preview.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void draw();
	void update();

	void arrangePreviews();
	//void onMouseClickedInPreview(int e);

	//--------------------------------------------------------------

	shared_ptr<ofAppBaseWindow> mainWindow;				// The Window of the main app

	vector<shared_ptr<vmVideoSource>> videoSources;		// All the video sources
	vector<shared_ptr<outputWindowApp>> outputWindowApps;//All the output windows

	vector<shared_ptr<preview>> previews;

};
