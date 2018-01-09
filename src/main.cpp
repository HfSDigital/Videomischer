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


									// Main (Mixer-UI) Window
	settings.width = 380;
	settings.height = 600;
	settings.title = "Videomischer";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	// Output Window 01
	settings.width = 1280;
	settings.height = 720;
	settings.title = "Display 1";
	settings.shareContextWith = mainWindow;		// .. um auf die Texturen eines anderen Fensters zuzugreifen
	shared_ptr<ofAppBaseWindow> outBaseWindow01 = ofCreateWindow(settings);

	// Output Window 02
	settings.width = 1280;
	settings.height = 720;
	settings.title = "Display 2";
	settings.shareContextWith = mainWindow;		// .. um auf die Texturen eines anderen Fensters zuzugreifen
	shared_ptr<ofAppBaseWindow> outBaseWindow02 = ofCreateWindow(settings);

	// Output Window 03
	settings.width = 640;
	settings.height = 360;
	settings.title = "Display 3";
	settings.shareContextWith = mainWindow;		// .. um auf die Texturen eines anderen Fensters zuzugreifen
	shared_ptr<ofAppBaseWindow> outBaseWindow03 = ofCreateWindow(settings);



	shared_ptr<outputWindow> outputWindow01 = make_shared<outputWindow>();
	shared_ptr<outputWindow> outputWindow02 = make_shared<outputWindow>();
	shared_ptr<outputWindow> outputWindow03 = make_shared<outputWindow>();
	shared_ptr<ofApp> mainApp = make_shared<ofApp>();

	mainApp->outputWindow01 = outputWindow01;				// um von der Haupt-App (ofApp) auf die Output-App zugreifen zu können
	mainApp->outputWindow02 = outputWindow02;				// um von der Haupt-App (ofApp) auf die Output-App zugreifen zu können
	mainApp->outputWindow03 = outputWindow03;				// um von der Haupt-App (ofApp) auf die Output-App zugreifen zu können

	ofRunApp(outBaseWindow01, outputWindow01);
	ofRunApp(outBaseWindow02, outputWindow02);
	ofRunApp(outBaseWindow03, outputWindow03);
	ofRunApp(mainWindow, mainApp);

	ofRunMainLoop();

}
