#include "vmPicture.h"

//--------------------------------------------------------------

vmPicture::vmPicture(string filename)
{
	picture.load(filename);
	title = filename.substr(filename.find_last_of("\\") + 1);
	//title = title.substr(0, title.find_last_of("."));
}

//--------------------------------------------------------------

void vmPicture::update(){}

//--------------------------------------------------------------

void vmPicture::draw(int x, int y, int w, int h)
{
	picture.draw(x, y, w, h);
}

//--------------------------------------------------------------

void vmPicture::play(){}

//--------------------------------------------------------------

void vmPicture::stop(){}

//--------------------------------------------------------------

void vmPicture::setVolume(float v) {}

//--------------------------------------------------------------

void vmPicture::setLoop(bool l) {}

//--------------------------------------------------------------

ofTexture* vmPicture::getTexture()
{
	return &picture.getTexture();
}