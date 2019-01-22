#include "vmPlayer.h"

//--------------------------------------------------------------

vmPlayer::vmPlayer(string filename)
{
	if (soundStream.setup(this, 2, 0, 48000, 512, 4))
	{
		videoPlayer.setupAudioOut(2, 48000);
	}
	else
	{
		cout << "no sound device detected" << endl;
	}
	
	this->filename = filename;
	title = filename.substr(filename.find_last_of("\\") + 1);
	//title = title.substr(0, title.find_last_of("."));
}

//--------------------------------------------------------------

void vmPlayer::update() 
{
	videoPlayer.update();
}

//--------------------------------------------------------------

void vmPlayer::draw(int x, int y, int w, int h)
{
	videoPlayer.draw(x, y, w, h);
}

//--------------------------------------------------------------

void vmPlayer::play()
{
	if (!videoPlayer.isLoaded())
	{
		videoPlayer.load(filename);
	}

	if (!videoPlayer.getIsPlaying())
	{
		videoPlayer.setPosition(0);
	}
	videoPlayer.play(); 
}

//--------------------------------------------------------------

void vmPlayer::pause()
{
	if (videoPlayer.getIsPlaying())
	{
		videoPlayer.setPaused(true);
	} else 
	{
		videoPlayer.setPaused(false);
	}
}

//--------------------------------------------------------------

void vmPlayer::stop()
{
	videoPlayer.stop();
	videoPlayer.unload();
}

//--------------------------------------------------------------

void vmPlayer::setVolume(float v) {
	cout << "volume: " << v << endl;
	videoPlayer.setVolume(v);
}

//--------------------------------------------------------------

void vmPlayer::setLoop(bool l) {
	videoPlayer.setLoop(l);
}

//--------------------------------------------------------------

ofTexture* vmPlayer::getTexture()
{
	return &videoPlayer.getTexture();
}

//--------------------------------------------------------------

void vmPlayer::audioOut(float * output, int bufferSize, int nChannels) {
	videoPlayer.audioOut(output, bufferSize, nChannels);
}
