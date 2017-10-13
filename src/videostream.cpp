#include "videostream.h"


int videostream::previewIDCounter = 0;

videostream::videostream(int devideID)
{
	initPreview();
	streamtype = webcam;

	width = 1280;
	height = 720;

	videoGrabber.setDeviceID(devideID);
	videoGrabber.setDesiredFrameRate(60);
	videoGrabber.initGrabber(width, height);

	title =  "live cam";
}



videostream::videostream(string filename)
{
	initPreview();
	streamtype = videoFile;

	videoPlayer.load(filename);

	width = videoPlayer.getWidth();
	height = videoPlayer.getHeight();

	title = filename;
}

videostream::~videostream() {}

void videostream::initPreview() {
	previewID = previewIDCounter++;

	cout << "preview id: " << previewID << endl;
	
	ofRegisterMouseEvents(this);

	previewWidth = 160;
	previewHeight = 100;

	previewFbo.allocate(previewWidth, previewHeight, GL_RGBA, ofFbo::maxSamples());
}


void videostream::update() {
	previewFbo.begin();
	switch ( streamtype )
	{
	case videoFile:
		videoPlayer.update();  // it's weird, but ... do this in draw(), not in update! 
		videoPlayer.draw(0, 0, previewWidth, previewHeight);
		break;

	case webcam:
		videoGrabber.update();
		videoGrabber.draw(0, 0, previewWidth, previewHeight);
		break;

	default:
		break;
	}
	previewFbo.end();
}

void videostream::drawPreview(int x = 0, int y = 0) {
	this->x = x;
	this->y = y;
	previewFbo.draw(x, y, previewWidth, previewHeight);
	if(isMouseOver){
		ofPushStyle();
		ofNoFill();
		ofSetColor(guiColors::border);
		ofDrawRectangle(x, y, previewWidth, previewHeight);
		ofPopStyle();
	}
}

ofTexture videostream::getTexture() {
	switch (streamtype)
	{
	case videoFile:
		return videoPlayer.getTexture();
		break;

	case webcam:
		return videoGrabber.getTexture();
		break;

	default:
		break;
	}
}

int videostream::getWidth() {
	return width;
}

int videostream::getHeight() {
	return height;
}

int videostream::getPreviewWidth() {
	return previewWidth;
}

int videostream::getPreviewHeight() {
	return previewHeight;
}
ofVec2f videostream::getPosition() {
	return ofVec2f(x, y);
}
string videostream::getTitle() {
	return title;
}

void videostream::mouseMoved(ofMouseEventArgs & args) {
	isMouseOver = inside(args.x, args.y);		// only needed to draw a border around the preview when mouse is hovering
}

void videostream::mouseDragged(ofMouseEventArgs & args) {}
void videostream::mousePressed(ofMouseEventArgs & args) {
	if (inside(args.x, args.y)) {
		ofNotifyEvent(clickedInside, previewID, this);
	}
}
void videostream::mouseReleased(ofMouseEventArgs & args) {}
void videostream::mouseScrolled(ofMouseEventArgs & args) {}
void videostream::mouseEntered(ofMouseEventArgs & args) {}
void videostream::mouseExited(ofMouseEventArgs & args) {}


//this function checks if the passed arguments are inside the preview rectangle.
bool videostream::inside(float _x, float _y) {
	return ((_x > x) && (_x < x + previewWidth) && (_y > y) && (_y < y + previewHeight));
}




