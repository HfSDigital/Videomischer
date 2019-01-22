#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")  

#include "ofMain.h"
#include "ofAppGLFWWindow.h"

#include "ofApp.h"

//========================================================================

int main() {
	ofGLFWWindowSettings settings;
	int w = 1600;
	settings.width = w;
	settings.height = w / 8;
	settings.setPosition(ofVec2f(globals::padding, globals::padding*4));
	settings.title = "Videomischer";

	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp = make_shared<ofApp>();


	// output Windows
	//settings.shareContextWith = mainWindow;
	//settings.width = 640;
	//settings.height = 360;

	//for (int i = 0; i < 1; i++)
	//{
	//	settings.setPosition(ofVec2f(globals::padding * (i+2), globals::padding * 4* (i+2)));
	//	settings.title = "output window #" + to_string(mainApp->outputWindowApps.size());
	//	shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);

	//	mainApp->outputWindowApps.push_back(make_shared<outputWindowApp>());
	//	ofRunApp(window, mainApp->outputWindowApps.back());
	//}

	mainApp->mainWindow = mainWindow;
	ofRunApp(mainWindow, mainApp);

	ofRunMainLoop();
}
