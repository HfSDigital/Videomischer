#include "vmVideoSource.h"

//--------------------------------------------------------------

int vmVideoSource::idCounter = 0;

//--------------------------------------------------------------

vmVideoSource::vmVideoSource(){
	id = idCounter;
	idCounter++;
	cout << "vmVideoSource-ID: " << id << endl;
}

//--------------------------------------------------------------

vmVideoSource::~vmVideoSource()
{
	cout << "Destructor vmVideoSource" << endl;
}

//--------------------------------------------------------------

void vmVideoSource::printName() {
	cout << "Name: " << title << endl;
}

//--------------------------------------------------------------

void vmVideoSource::draw(int x, int y, int w, int h) {}
void vmVideoSource::update() {}
ofTexture* vmVideoSource::getTexture() { return NULL; }
void vmVideoSource::play() {}
void vmVideoSource::pause() {}
void vmVideoSource::stop() {}
void vmVideoSource::setVolume(float v) {}
void vmVideoSource::setLoop(bool l) {}
void vmVideoSource::receiveKeyInput(int key) {}