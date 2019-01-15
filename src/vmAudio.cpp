#include "vmAudio.h"

//--------------------------------------------------------------

vmAudio::vmAudio(string filename)
{
	fbo.allocate(128, 128, GL_RGBA);

	this->filename = filename;
	title = filename.substr(filename.find_last_of("\\") + 1);
	//title = title.substr(0, title.find_last_of("."));

	audio.load(filename);

	playInBackground = true;

}

//--------------------------------------------------------------

void vmAudio::update()
{
}

//--------------------------------------------------------------

void vmAudio::draw(int x, int y, int w, int h)
{
	fbo.begin();
	ofBackground(0);
	ofSoundGetSpectrum(256);
	//ofFill();
	//ofSetColor(ofColor::greenYellow);
	//ofCircle(64,64, 32);
	fbo.end();

	fbo.draw(x, y, w, h);
}

//--------------------------------------------------------------

void vmAudio::play()
{
	audio.isPlaying() ? audio.stop() : audio.play();
}

//--------------------------------------------------------------

void vmAudio::stop()
{
	//audio.stop();
}

//--------------------------------------------------------------

void vmAudio::setVolume(float v) {
	audio.setVolume(v);
}

//--------------------------------------------------------------

void vmAudio::setLoop(bool l) {
	audio.setLoop(l);
}

//--------------------------------------------------------------

ofTexture* vmAudio::getTexture()
{
	return &fbo.getTexture();
}

//--------------------------------------------------------------

void vmAudio::audioOut(float * output, int bufferSize, int nChannels) {
//	videoPlayer.audioOut(output, bufferSize, nChannels);
}
