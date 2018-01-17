#include "ofMain.h"
#include "ofAppGLFWWindow.h"

#include "ofApp.h"
#include "outputWindow.h"

//========================================================================
int main( ){
	ofGLFWWindowSettings settings;	//ofGLFWindowSettings settings;

	// Main (Mixer-UI) Window
	settings.width = 1280;
	settings.height = 720;
	settings.title = "Videomischer";
	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	// Vector (List) for all Base Windows
	vector<shared_ptr<ofAppBaseWindow>> outBaseWindows;

	// Output Window 01
	settings.shareContextWith = mainWindow;		// .. um auf die Texturen eines anderen Fensters zuzugreifen
	settings.width = 640;
	settings.height = 360;
	settings.title = "Display 0";
	outBaseWindows.push_back(ofCreateWindow(settings));

	// Output Window 02
	settings.title = "Display 1";
	outBaseWindows.push_back(ofCreateWindow(settings));

	// Output Window 03
	settings.title = "Display 2";
	outBaseWindows.push_back(ofCreateWindow(settings));

	vector<shared_ptr<outputWindow>> outputWindows;
	shared_ptr<ofApp> mainApp = make_shared<ofApp>();

	for (int i = 0; i < outBaseWindows.size(); i++) {
		outputWindows.push_back(make_shared<outputWindow>());
		mainApp->outputWindows.push_back(outputWindows[i]);
		ofRunApp(outBaseWindows[i], outputWindows[i]);
	}
	ofRunApp(mainWindow, mainApp);

	ofRunMainLoop();

}
