#include "ofMain.h"
#include "ofAppGLFWWindow.h"

#include "ofApp.h"
#include "outputWindow.h"

//========================================================================
int main( ){
	//mainWindow.setNumSamples(8);  
	//mainWindow.setMultiDisplayFullscreen(true); //this makes the fullscreen window span across all your monitors  

	//ofAppGLFWWindow mainWindow;
	//ofSetupOpenGL(&mainWindow, 1600,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());


	ofGLFWWindowSettings settings;	//ofGLFWindowSettings settings;

	settings.width = 1280;
	settings.height = 720;
	settings.title = "Beamer";
	shared_ptr<ofAppBaseWindow> outWindow = ofCreateWindow(settings);


	settings.width = 380;
	settings.height = 600;
	settings.title = "Videomischer";
	settings.shareContextWith = outWindow;		// .. um auf die Texturen eines anderen Fensters zuzugreifen
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);


	shared_ptr<outputWindow> outputApp = make_shared<outputWindow>();
	shared_ptr<ofApp> mainApp = make_shared<ofApp>();

	mainApp->outputApp = outputApp;				// um von der Haupt-App (ofApp) auf die Output-App zugreifen zu können

	ofRunApp(outWindow, outputApp);
	ofRunApp(mainWindow, mainApp);

	ofRunMainLoop();

}
