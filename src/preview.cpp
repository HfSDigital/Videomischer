#include "preview.h"


//--------------------------------------------------------------

preview::preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource, shared_ptr<ofTrueTypeFont> std_font)
{
	this->outputWindow = outputWindow;
	this->videoSource = videoSource;
	this->std_font = std_font;
	size = ofVec2f(160, 90);
	isMouseOver = false;
}


//--------------------------------------------------------------

preview::~preview()
{
	cout << "closing preview " << videoSource->title << " output window: " << outputWindow->id << endl;;
}

//--------------------------------------------------------------

void preview::setSize(ofVec2f size) {
	this->size = size;
}

//--------------------------------------------------------------

void preview::setPos(ofVec2f pos) {
	this->pos = pos;
}

//--------------------------------------------------------------

void preview::draw() {

	// red border for textures that are currently displayed
	if (outputWindow->outTexture == videoSource->getTexture()) {
		ofSetColor(ofColor::red);
		ofRect(pos.x - globals::borderwidth, pos.y - globals::borderwidth, size.x + globals::borderwidth * 2, size.y + globals::borderwidth * 2);
	}

	ofSetColor((isMouseOver > 0) ? ofColor::grey : ofColor::white);

	// draw preview thumbnail
	videoSource->draw(pos.x, pos.y, size.x, size.y);

	// draw title of videoSource
	ofPushStyle();
	ofNoFill();
	ofSetColor(ofColor::white);

	std_font->drawString(titleTrimmed, pos.x, pos.y - globals::padding/2);
	//ofDrawBitmapString(titleTrimmed, pos.x, pos.y - globals::padding / 2);

	if (isMouseOver)
	{
		string s = (isMouseOver > 1) ? "Audio Off" : "Audio On";
		int w = std_font->stringWidth(s);
		int h = std_font->stringHeight(s);
		ofLine(pos.x, pos.y + size.y / 2, pos.x + size.x/2-w/2-h, pos.y + size.y / 2);
		ofLine(pos.x+size.x/2+w/2+h, pos.y + size.y / 2, pos.x + size.x, pos.y + size.y / 2);
		std_font->drawString(s, pos.x + size.x/2 - w/2, pos.y + size.y / 2 + h/2);
		//ofDrawBitmapString(s, pos.x + size.x / 2 - w / 2, pos.y + size.y / 2 + h / 2);
	}
	ofPopStyle();
}

//--------------------------------------------------------------

void preview::trimTitle()
{
	titleTrimmed = "";
	int i = 8;
	do {
		i++;
		titleTrimmed = videoSource->title.substr(0, i);
	} while (std_font->stringWidth(titleTrimmed) < size.x && i <= videoSource->title.length());
}

//--------------------------------------------------------------

int preview::inside(float _x, float _y, bool hasClicked) {
	// this function checks if the passed arguments are inside the preview rectangle.
	// return 1 if click was in upper half, return 2 if click was in lower half of the region

	if ((_x > pos.x) && (_x < pos.x + size.x) && (_y > pos.y) && (_y < pos.y + size.y / 2))
	{
		isMouseOver = 1;
	}
	else if ((_x > pos.x) && (_x < pos.x + size.x) && (_y >= pos.y + size.y / 2) && (_y < pos.y + size.y)) 
	{
		isMouseOver = 2;
	}
	else
	{
		isMouseOver = 0;
	}

	if (isMouseOver && hasClicked) {
		cout << "clicked inside " << videoSource->title << " " << videoSource->id << " output window: " << outputWindow->id << endl;
		outputWindow->setTexture(videoSource->getTexture());
		outputWindow->videosourceID = videoSource->id;
		videoSource->play();
		videoSource->setVolume((isMouseOver == 1) ? 1.0f : 0.0f);
	}

	return isMouseOver;
}


