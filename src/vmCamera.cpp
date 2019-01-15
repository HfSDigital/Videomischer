#include "vmCamera.h"

//--------------------------------------------------------------

vmCamera::vmCamera(int deviceID)
{
	//videoGrabber = make_shared<ofVideoGrabber>();
	
	videoGrabber.setDeviceID(deviceID);
	videoGrabber.setDesiredFrameRate(30);
	videoGrabber.initGrabber(1280, 720);
	//videoGrabber.videoSettings();

	title = "cam#" + to_string(deviceID);
}

//--------------------------------------------------------------

void vmCamera::update() 
{
	videoGrabber.update();
}

//--------------------------------------------------------------

void vmCamera::draw(int x, int y, int w, int h)
{
	videoGrabber.draw(x, y, w, h);
}

//--------------------------------------------------------------

ofTexture* vmCamera::getTexture() 
{
	return &videoGrabber.getTexture();
}

//--------------------------------------------------------------

void vmCamera::play(){}

//--------------------------------------------------------------

void vmCamera::stop(){}

//--------------------------------------------------------------

void vmCamera::setVolume(float f){}

//--------------------------------------------------------------

void vmCamera::setLoop(bool l) {}