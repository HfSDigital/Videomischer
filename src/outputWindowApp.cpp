#include "outputWindowApp.h"

int outputWindowApp::idCounter = 0;

//--------------------------------------------------------------

outputWindowApp::outputWindowApp() {
	outTexture = nullptr;
	id = idCounter;
	idCounter++;
	cout << "outputWindowApp-ID: " << id << endl;
}

//--------------------------------------------------------------


void outputWindowApp::setTexture(ofTexture* _outTexture)
{
	outTexture = _outTexture;
}

//--------------------------------------------------------------

void outputWindowApp::setup(){}

//--------------------------------------------------------------

void outputWindowApp::update(){}

//--------------------------------------------------------------

void outputWindowApp::draw() 
{
	if (outTexture) outTexture->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
}

//--------------------------------------------------------------

void outputWindowApp::keyPressed(int key) {
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}