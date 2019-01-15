#include "preview.h"

//--------------------------------------------------------------

preview::preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource, shared_ptr<ofTrueTypeFont> std_font)
{
	//keyboardShortcut = previewID++;
	keyboardShortcut = -1;
	this->outputWindow = outputWindow;
	this->videoSource = videoSource;
	this->std_font = std_font;
	size = ofVec2f(160, 90);
	isMouseOver = false;
	waitForKey = false;

	//bMute = false;
	//videoSource->setVolume(bMute ? 0.0f : 1.0f);
	//bLoop = false;
	//videoSource->setLoop(bLoop);

	const int btn_size = 9;
	// add buttons;
	btns.push_back(btn());
	btns.back().name = "mute";
	btns.back().x = btn_size;
	btns.back().y = btn_size * 1;
	btns.back().r = btn_size;
	btns.back().color = ofColor::lightGrey;
	btns.back().isMouseOver = false;

	btns.push_back(btn());
	btns.back().name = "loop";
	btns.back().x = btn_size;
	btns.back().y = btn_size * 3;
	btns.back().r = btn_size;
	btns.back().color = ofColor::lightGrey;
	btns.back().isMouseOver = false;

	btns.push_back(btn());
	btns.back().name = "shortcut";
	btns.back().x = btn_size;
	btns.back().y = btn_size * 5;
	btns.back().r = btn_size;
	btns.back().color = ofColor::lightGrey;
	btns.back().isMouseOver = false;
}


//--------------------------------------------------------------

preview::~preview(){}

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
	ofSetColor(ofColor::grey);
	std_font->drawString(titleTrimmed, pos.x, pos.y - 2);
	ofPopStyle();

	// draw buttons for mute, loop and shortkey
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	for (int i = 0; i < btns.size(); i++) {		
		string s = btns.at(i).name;
		
		if (s == "mute") {
			s = videoSource->bMute ? "muted" : "m";
		}
		else if (s == "loop") {
			s = videoSource->bLoop ? "looping" : "lo";
		}
		else if (s == "shortcut") {
			s = "Ctrl + " + string(1, keyboardShortcut);
		}
		
		float h = btns.at(i).r * 2;
		float w = std_font->stringWidth(s) + btns.at(i).r;
		ofFill();
		ofSetColor(btns.at(i).isMouseOver ? ofColor::white : btns.at(i).color);
		
		if (btns.at(i).name == "shortcut" && waitForKey) ofSetColor(ofColor::red);

		ofDrawRectRounded(btns.at(i).x - btns.at(i).r, btns.at(i).y - btns.at(i).r, w, h, btns.at(i).r);
		ofSetColor(btns.at(i).isMouseOver ? ofColor::black : ofColor::black);
		std_font->drawString(s, btns.at(i).x - btns.at(i).r/2, btns.at(i).y + btns.at(i).r/2);
	}
	ofPopMatrix();
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

void preview::inside(float _x, float _y, bool hasClicked) {
	// this function checks if the passed arguments are inside the preview rectangle.

	// check buttons
	bool insideButtons = false;
	for (int i = 0; i < btns.size(); i++) {
		if (ofDist(_x, _y, pos.x + btns.at(i).x, pos.y + btns.at(i).y) < btns.at(i).r) {
			btns.at(i).isMouseOver = true;
			insideButtons = true;
			if (hasClicked) {
				cout << btns.at(i).name << endl;
				if (btns.at(i).name == "mute") {
					videoSource->bMute = !videoSource->bMute;
					videoSource->setVolume(videoSource->bMute ? 0.0f : 1.0f);
				}
				else if (btns.at(i).name == "loop") {
					videoSource->bLoop = !videoSource->bLoop;
					videoSource->setLoop(videoSource->bLoop);
				}
				else if (btns.at(i).name == "shortcut") {
					waitForKey = true;
				}
			}
		}
		else {
			btns.at(i).isMouseOver = false;
		}
	}

	if ((_x > pos.x) && (_x < pos.x + size.x) && (_y > pos.y) && (_y < pos.y + size.y))
	{
		isMouseOver = 1;

		// if we click and we're not inside of one of the tiny buttons, play the video
		if (!insideButtons && hasClicked) {
			showVideo();
		}
	}
	else
	{
		isMouseOver = 0;
	}

}

//--------------------------------------------------------------

void preview::showVideo() {

	cout << "playing " << videoSource->title << " " << videoSource->id 
		<< " output window: " << outputWindow->id << " keyboardShortcut: " << keyboardShortcut
		<< " loop: " << videoSource->bLoop << " audio: " << videoSource->bMute << endl;
	
	if (!videoSource->playInBackground) {
		outputWindow->setTexture(videoSource->getTexture());
		outputWindow->videosourceID = videoSource->id;
	}

	videoSource->play();
}

