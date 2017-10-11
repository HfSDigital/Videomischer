#include "outputWindow.h"

//--------------------------------------------------------------
void outputWindow::setup() {
	outTexture.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA);
}

//--------------------------------------------------------------
void outputWindow::update() {
}

//--------------------------------------------------------------
void outputWindow::draw() {
	outTexture.draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

}

void outputWindow::keyPressed(int key) {
	if (key == 'f')
	{
		ofToggleFullscreen();
	}
}