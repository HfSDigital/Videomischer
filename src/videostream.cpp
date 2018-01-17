#include "videostream.h"
#include "RtAudio.h"

int videostream::previewIDCounter = 0;

videostream::videostream()
{
	previewIsInitialized = false;
	streamtype = empty;
	ofFile img("Solid_black.png");
	blackimage.loadImage(img);
	title = "black";
}
	
videostream::videostream(int deviceID)
{
	previewIsInitialized = false;
	streamtype = webcam;

	width = 1280;
	height = 720;
	

	videoGrabber.setDeviceID(deviceID);
	
	videoGrabber.setDesiredFrameRate(25);

	title = "device-id: " + to_string(deviceID);
	
	if (!videoGrabber.initGrabber(width, height)) {
		throw deviceID;
	}
}

videostream::videostream(string filename)
{
	previewIsInitialized = false;
	streamtype = videoFile;

	cout << "ofSoundStream Device List: " << endl;
	for (int i = 0; i < soundStream.getDeviceList().size(); i++) {
		cout << "device #" + to_string(i) + ": " + soundStream.getDeviceList()[i].name << endl;
	}

	int sampleRates[] = {44100, 48000};

	for (int i = 0; i < size(sampleRates); i++) {
		if (soundStream.setup(this, 2, 0, sampleRates[i], 512, 4)) {
			cout << "[VM] audio setup okay, samplerate " << sampleRates[i] << endl;
			videoPlayer.setupAudioOut(2, sampleRates[i]);
			break;
		}
		else {
			cout << "[VM ERROR] audio setup with samplerate " << sampleRates[i] << " failed" << endl;
		}
	}


	videoPlayer.setLoop(false);
	videoPlayer.load(filename);
	videoPlayer.stop();

	width = videoPlayer.getWidth();
	height = videoPlayer.getHeight();
	
	title = filename.substr(filename.find_last_of("\\"));
}
void videostream::audioOut(float * output, int bufferSize, int nChannels) {
	videoPlayer.audioOut(output, bufferSize, nChannels);
}


videostream::~videostream() {}

void videostream::play() {
	if (streamtype == videoFile) {
		if (!videoPlayer.getIsPlaying()) {
			videoPlayer.setPosition(0);
			videoPlayer.play();
		}
	}
}

void videostream::close() {
	videoGrabber.close();
}

void videostream::initPreview() {
	previewID = previewIDCounter++;

	previewFbo.allocate(previewWidth, previewHeight, GL_RGBA, ofFbo::maxSamples());
	previewIsInitialized = true;
}

void videostream::addPreview(ofVec2f pos, int outDisplay, ofVec2f size) {
	previewWidth = size.x;
	previewHeight = size.y;

	if(!previewIsInitialized) initPreview();

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

	case empty:
		blackimage.draw(0, 0, previewWidth, previewHeight);
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
			ofSetColor(ofColor::white);
			ofDrawBitmapString(title, previews[i]->pos.x, previews[i]->pos.y);
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
		return blackimage.getTexture();
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





