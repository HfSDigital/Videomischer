#include "preview.h"


preview::preview(int id, ofVec2f pos, ofVec2f size, int outDisplay) {
	ofRegisterMouseEvents(this);
	this->id = id;
	this->pos = pos;
	this->size = size;
	this->outDisplay = outDisplay;
}


void preview::mouseMoved(ofMouseEventArgs & args) {
	isMouseOver = inside(args.x, args.y);		// only needed to draw a border around the preview when mouse is hovering
}

void preview::mouseDragged(ofMouseEventArgs & args) {}
void preview::mousePressed(ofMouseEventArgs & args) {
	if (inside(args.x, args.y)) {
		ofVec2f e;
		e.x = id;
		e.y = outDisplay;
		ofNotifyEvent(clickedInside, e, this);
	}
}
void preview::mouseReleased(ofMouseEventArgs & args) {}
void preview::mouseScrolled(ofMouseEventArgs & args) {}
void preview::mouseEntered(ofMouseEventArgs & args) {}
void preview::mouseExited(ofMouseEventArgs & args) {}

//this function checks if the passed arguments are inside the preview rectangle.
bool preview::inside(float _x, float _y) {
	return ((_x > pos.x) && (_x < pos.x + size.x) && (_y > pos.y) && (_y < pos.y + size.y));
}
