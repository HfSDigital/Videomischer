#pragma once

#include "ofMain.h"


//#include "IPVideoGrabber.h"
#include "ofxAvVideoPlayer.h"
#include "ofxGui.h"
#include "ofxJSON.h"

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

	void windowResized(int w, int h);
	//void keyPressed(int key);

	void keycodePressed(ofKeyEventArgs& e);
	void keycodeReleased(ofKeyEventArgs& e);

	void addOutputWindow(ofVec2f size, ofVec2f position, int id = -1);

	void showHelp(int x, int y);

	void exit();
	//void onMouseClickedInPreview(int e);


	void mouseMoved(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	void mouseScrolled(ofMouseEventArgs & args);
	void mouseEntered(ofMouseEventArgs & args);
	void mouseExited(ofMouseEventArgs & args);



	//--------------------------------------------------------------

	shared_ptr<ofAppBaseWindow> mainWindow;				// The Window of the main app

	vector<shared_ptr<vmVideoSource>> videoSources;		// All the video sources
	vector<shared_ptr<outputWindowApp>> outputWindowApps;//All the output windows
	vector<shared_ptr<preview>> previews;

	shared_ptr<ofTrueTypeFont> std_font;

	ofVec2f windowSize;
	ofVec2f windowPosition;


	string saveFile = "settings.json";
	ofxJSONElement saveFileElement;

	bool bCTRLpressed, bALTpressed, bSHIFTpressed;


};
