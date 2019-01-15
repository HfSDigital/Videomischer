#include "vmChat.h"

//--------------------------------------------------------------

vmChat::vmChat()
{
	fbo.allocate(1920, 1200, GL_RGBA);
	title = "chat";

	currentPerson = 0;
	totalHeight = 0;
	_totalHeight = 0;
	portraitSize = 128;

	messengerFont.load("chat/Myriad Pro Regular.ttf", 32);

	portraitThumbs.push_back(ofImage("chat/person1.png"));
	portraitThumbs.push_back(ofImage("chat/person2.png"));

	msgArrivedSnd.load("chat/incoming.wav");
	keyPressedSnd.load("chat/keyclick.wav");
}

//--------------------------------------------------------------

void vmChat::draw(int x, int y, int w, int h)
{
	fbo.begin();

	ofBackground(238);

	ofFill();

	float _y = (_totalHeight > fbo.getHeight() * 0.8) ? fbo.getHeight() * 0.9 - _totalHeight : fbo.getHeight() * 0.1;

	float _x = 240;

	totalHeight = 0;
	for (Message &message : messages) {

		// profile picture START
		ofSetColor(255);
		int portraitPosX = _x;
		if (message.personID == 0) {
			portraitPosX = fbo.getWidth() - _x - portraitSize;
		}
		portraitThumbs.at(message.personID).draw(portraitPosX, _y + totalHeight, portraitSize, portraitSize);
		// profile picture END


		// speech bubble START
		float radius    = portraitSize / 3.5;
		float msgHeight = messengerFont.getStringBoundingBox(message.message, 0, 0).height;
		float msgWidth  = messengerFont.getStringBoundingBox(message.message, 0, 0).width;

		if (msgHeight < messengerFont.getLineHeight())	// set height of the bubble to a minimum
			msgHeight = messengerFont.getLineHeight();

		if (msgWidth < radius) msgWidth = radius;		// set width of the bubble to a minimum

		vector<ofPoint> p;		// edge-points of the bubble
		{
			p.push_back(ofPoint(_x + portraitSize / 2 + radius / 2, _y + totalHeight));
			p.push_back(ofPoint(p.back().x + portraitSize / 2, p.back().y + portraitSize / 2));
			p.push_back(ofPoint(p.back().x, p.back().y + msgHeight - messengerFont.getLineHeight()));
			p.push_back(ofPoint(p.back().x + portraitSize / 2, p.back().y + portraitSize / 2));
			p.push_back(ofPoint(p.back().x + msgWidth - radius, p.back().y));
			p.push_back(ofPoint(p.back().x + portraitSize / 2, p.back().y - portraitSize / 2));
			p.push_back(ofPoint(p.back().x, p.back().y - msgHeight + messengerFont.getLineHeight()));
			p.push_back(ofPoint(p.back().x - portraitSize / 2, p.at(0).y));
		}

		vector<ofPoint> c;		// control points for the bezier-curves
		{
			c.push_back(ofPoint(p.at(0).x + radius, p.at(0).y));
			c.push_back(ofPoint(p.at(1).x, p.at(1).y - radius));
			c.push_back(ofPoint(p.at(2).x, p.at(2).y + radius));
			c.push_back(ofPoint(p.at(3).x - radius, p.at(3).y));
			c.push_back(ofPoint(p.at(4).x + radius, p.at(4).y));
			c.push_back(ofPoint(p.at(5).x, p.at(5).y + radius));
			c.push_back(ofPoint(p.at(6).x, p.at(6).y - radius));
			c.push_back(ofPoint(p.at(7).x + radius, p.at(7).y));
		}

		
		ofPushMatrix();
			if (message.personID == 0) {
				ofTranslate(fbo.getWidth(), 0);	// mirror speech bubble
				ofScale(-1.0, 1.0);				//		 - " -
				ofSetColor(255);
			}
			else
			{
				ofSetColor(52);
			}
			ofBeginShape();
				ofVertex(p.at(0));
				ofBezierVertex(c.at(0), c.at(1), p.at(1));
				ofVertex(p.at(2));
				ofBezierVertex(c.at(2), c.at(3), p.at(3));
				ofVertex(p.at(4));
				ofBezierVertex(c.at(4), c.at(5), p.at(5));
				ofVertex(p.at(6));
				ofBezierVertex(c.at(6), c.at(7), p.at(7));
				ofVertex(p.at(0));
			ofEndShape();
		ofPopMatrix();
		// speech bubble END


		// message text START
		ofSetColor(message.personID == 0 ? 0 : 255);

		int messagePosX = _x + float(portraitSize) * 1.4;
		if (message.personID == 0) {
			messagePosX = fbo.getWidth() - messagePosX - msgWidth;
		}

		string m = message.message;
		int blinkspeed = 800;
		if (&message == &messages.back()) {			// if it's the last message, at a blinking cursor
			if (ofGetElapsedTimeMillis() % blinkspeed > blinkspeed / 2) m += "|";
		}
		messengerFont.drawString(m, messagePosX, _y + totalHeight + portraitSize / 2);
		// message text END


		msgHeight = p.at(3).y - p.at(0).y;
		totalHeight += msgHeight;
		_totalHeight = totalHeight;
	}

	fbo.end();

	fbo.draw(x, y, w, h);
}

//--------------------------------------------------------------

ofTexture* vmChat::getTexture()
{
	return &fbo.getTexture();
}

//--------------------------------------------------------------

void vmChat::receiveKeyInput(int key) {
	char c = key;

	if (key == '1' || key == '2') {
		currentPerson = (c - '0') - 1;	// just learned: a neat trick to convert numeric char to int ^^

		if (messages.size() == 0 || messages.back().message.size() > 0) {
			messages.push_back(Message());
		}
		messages.back().personID = currentPerson;

		msgArrivedSnd.play();
	}
	else/* if (key < 255)*/ {
		if (messages.size() > 0) {

			keyPressedSnd.play();

			addKeyToString(messages.back().message, key);

			lineBreak(messages.back().message);
		}
	}
}

//--------------------------------------------------------------

void vmChat::addKeyToString(string &message, int key) {
	if (key >= 32 && key <= 126) {		// standard letters
		messages.back().message += key;
	}
	else if (key == 228) {				// german umlaute
		messages.back().message += "ä";
	}
	else if (key == 246) {				// german umlaute
		messages.back().message += "ö";
	}
	else if (key == 252) {				// german umlaute
		messages.back().message += "ü";
	}
	else if (key == 196) {				// german umlaute
		messages.back().message += "Ä";
	}
	else if (key == 214) {				// german umlaute
		messages.back().message += "Ö";
	}
	else if (key == 220) {				// german umlaute
		messages.back().message += "Ü";
	}
	else if (key == 223) {				// german umlaute
		messages.back().message += "ß";
	}
	else if (key == 13) {				// carriage return
		if (messages.back().message > "") {
			messages.back().message += "\n";
		}
	}
	else if (key == 8) {				// backspace, subtract last character (if there is one)
		string _m = messages.back().message;
		if (_m.size() > 1) {
			_m = _m.substr(0, _m.size() - 1);
			messages.back().message = _m;
		}
		else if (_m.size() == 1) {
			messages.back().message = "";
		}
	}
}

//--------------------------------------------------------------

void vmChat::lineBreak(string &message) {
	unsigned foundBreak = message.find_last_of("\n");
	string lastLine = message.substr(foundBreak + 1);
	//are we over capacity? then let's insert a linebreak at the last space we find
	if (messengerFont.stringWidth(lastLine)>fbo.getWidth() * 0.5) {
		//so let's do it!
		//Find a whitespace
		unsigned foundSpace = lastLine.find_last_of(' ');
		message.replace(foundBreak + foundSpace + 1, 1, "\n");
	}
}