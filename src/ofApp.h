#pragma once

#include "ofMain.h"
#include "ofxAvVideoPlayer.h"
#include "outputWindow.h"

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		shared_ptr<outputWindow> outputApp;
		

		ofVideoGrabber videoGrabber;
		ofTexture videoTexture;

		ofxAvVideoPlayer videoPlayer;

		int camWidth;
		int camHeight;
		
		vector<ofFbo> previews;	// Die Previews
		int padding;			// Abstand zwischen den Preview Thumbnails
		int maxPreviews;		// Anzahl Previews (muss natürlich noch dynamisiert werden)
		int liveID;				// Der Index der Preview, die gerade auf den Beamer geschaltet ist
		
};
