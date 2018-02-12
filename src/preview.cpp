#include "preview.h"


//--------------------------------------------------------------

preview::preview(shared_ptr<outputWindowApp> outputWindow, shared_ptr<vmVideoSource> videoSource)
{
	ofRegisterMouseEvents(this);

	this->outputWindow = outputWindow;
	this->videoSource = videoSource;

	size = ofVec2f(160, 90);
	isMouseOver = false;

	std_font.loadFont("RobotoCondensed-Regular.ttf", 32);

}

//--------------------------------------------------------------

void preview::setSize(ofVec2f size) {
	this->size = size;
	float fontsize = ofClamp(size.x / 5, 8, 12);
	std_font.loadFont("RobotoCondensed-Regular.ttf", fontsize);
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

	std_font.drawString(titleTrimmed, pos.x, pos.y - globals::padding/2);
	if (isMouseOver)
	{
		string s = (isMouseOver > 1) ? "Audio Off" : "Audio On";
		int w = std_font.stringWidth(s);
		int h = std_font.stringHeight(s);
		ofLine(pos.x, pos.y + size.y / 2, pos.x + size.x/2-w/2-h, pos.y + size.y / 2);
		ofLine(pos.x+size.x/2+w/2+h, pos.y + size.y / 2, pos.x + size.x, pos.y + size.y / 2);
		std_font.drawString(s, pos.x + size.x/2 - w/2, pos.y + size.y / 2 + h/2);
	}
	ofPopStyle();

}

//--------------------------------------------------------------

void preview::trimTitle()
{
	titleTrimmed = videoSource->title;

	while (std_font.stringWidth(titleTrimmed) > size.x) {
		titleTrimmed = titleTrimmed.substr(0, titleTrimmed.size() - 1);;
	}
}

//--------------------------------------------------------------

void preview::mouseMoved(ofMouseEventArgs & args) {
	isMouseOver = inside(args.x, args.y);
}

//--------------------------------------------------------------

void preview::mousePressed(ofMouseEventArgs & args) {
	int in = inside(args.x, args.y);
	if (in) {
		cout << "clicked inside " << videoSource->title << " output window: " << outputWindow->id << endl;
		outputWindow->setTexture(videoSource->getTexture());
		videoSource->play();
		videoSource->setVolume((in==1)?1.0f:0.0f);
		//ofNotifyEvent(clickedInside, 0, this);
	}
}

//--------------------------------------------------------------

void preview::mouseDragged(ofMouseEventArgs & args) {}
void preview::mouseReleased(ofMouseEventArgs & args) {}
void preview::mouseScrolled(ofMouseEventArgs & args) {}
void preview::mouseEntered(ofMouseEventArgs & args) {}
void preview::mouseExited(ofMouseEventArgs & args) {}

//--------------------------------------------------------------

//this function checks if the passed arguments are inside the preview rectangle.
int preview::inside(float _x, float _y) {
	// return 1 if click was in upper half, return 2 if click was in lower half of the region
	if ((_x > pos.x) && (_x < pos.x + size.x) && (_y > pos.y) && (_y < pos.y + size.y / 2))
		return 1;
	else if ((_x > pos.x) && (_x < pos.x + size.x) && (_y >= pos.y + size.y/2) && (_y < pos.y + size.y))
		return 2;
	else 
		return 0;
}
