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

}



videostream::videostream(string filename)
{
	initPreview();
	streamtype = videoFile;

	videoPlayer.load(filename);

	width = videoPlayer.getWidth();
	height = videoPlayer.getHeight();

//	title = filename;
}

videostream::~videostream() {}

void videostream::initPreview() {
	previewID = previewIDCounter++;

	previewWidth = 160;
	previewHeight = 100;
	previewFbo.allocate(previewWidth, previewHeight, GL_RGBA, ofFbo::maxSamples());
}

void videostream::addPreview(ofVec2f pos, int outDisplay) {
	previews.push_back(new preview(previewID, pos, ofVec2f(previewWidth, previewHeight), outDisplay));
}





void videostream::update() {
	previewFbo.begin();
	switch ( streamtype )
	{
	case videoFile:
		videoPlayer.update();  // (it's weird, but ... do this in draw(), not in update!)
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


void videostream::drawPreview() {
	for (int i = 0; i < previews.size(); i++) {
		previewFbo.draw(previews[i]->pos.x, previews[i]->pos.y, previewWidth, previewHeight);
		if (previews[i]->isMouseOver) {
			ofPushStyle();
			ofNoFill();
			ofSetColor(guiColors::border);
			ofDrawRectangle(previews[i]->pos.x, previews[i]->pos.y, previewWidth, previewHeight);
			ofPopStyle();
		}
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
//ofVec2f videostream::getPosition() {
//	return ofVec2f(x, y);
//}
//string videostream::getTitle() {
//	return title;
//}





