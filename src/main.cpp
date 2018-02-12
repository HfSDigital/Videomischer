#include "ofMain.h"
#include "ofAppGLFWWindow.h"

#include "ofApp.h"

//========================================================================

int main() {
	ofGLFWWindowSettings settings;
	settings.width = 1920;
	settings.height = 700;
	settings.title = "Videomischer";

	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
	shared_ptr<ofApp> mainApp = make_shared<ofApp>();

	settings.shareContextWith = mainWindow;
	settings.width = 640;
	settings.height = 360;

	for (int i = 0; i < 3; i++)
	{
		settings.title = "output window #" + to_string(mainApp->outputWindowApps.size());
		shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);

		mainApp->outputWindowApps.push_back(make_shared<outputWindowApp>());
		ofRunApp(window, mainApp->outputWindowApps.back());
	}

	mainApp->mainWindow = mainWindow;
	ofRunApp(mainWindow, mainApp);

	ofRunMainLoop();
}



//--------------------------------------------------------------

void addOutput()
{
}
