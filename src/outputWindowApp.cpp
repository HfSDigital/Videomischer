#include "outputWindowApp.h"

vector<int> outputWindowApp::idCounter;

//--------------------------------------------------------------

outputWindowApp::outputWindowApp()
{
	outTexture = nullptr;
	isFullscreen = false;

	if (idCounter.size() > 0) 
		id = idCounter.back() + 1;
	else 
		id = 0;

	idCounter.push_back(id);

	isRunning = true;
	cout << "outputWindowApp-ID: " << id << endl;
}

//--------------------------------------------------------------

outputWindowApp::outputWindowApp(int _id)
{
	outTexture = nullptr;
	id = _id;
	idCounter.push_back(id);
	isRunning = true;
	cout << "outputWindowApp-ID: " << id << endl;
}

//--------------------------------------------------------------

void outputWindowApp::setTexture(ofTexture* _outTexture)
{
	outTexture = _outTexture;
}

//--------------------------------------------------------------

void outputWindowApp::setup(){
	// Everything we need to setup for the mapping
	clickedCorner = -1;
	cornerSize = 15;
	mouseInsideOutputWindowApp = false;

	originalCorners[0].set(0, 0);
	originalCorners[1].set(1, 0);
	originalCorners[2].set(1, 1);
	originalCorners[3].set(0, 1);

	distortedCorners[0].set(0, 0);
	distortedCorners[1].set(1, 0);
	distortedCorners[2].set(1 ,1);
	distortedCorners[3].set(0, 1);

	updateHomography();
}

//--------------------------------------------------------------

void outputWindowApp::update(){
	windowPosition.x = ofGetWindowPositionX();
	windowPosition.y = ofGetWindowPositionY();
}

//--------------------------------------------------------------

void outputWindowApp::draw() 
{
	ofBackground(0);
	
	if (outTexture) 
	{
		ofPushMatrix();
		ofMultMatrix(homography);
		outTexture->draw(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
		ofPopMatrix();

		// Draw 4 Points for mapping
		if (mouseInsideOutputWindowApp) {
			for (int i = 0; i < 4; i++)
			{
				ofPushStyle();
				ofSetColor(ofColor::yellow);
				ofEllipse(distortedCornersScreen[i], cornerSize, cornerSize);
				ofPopStyle();
			}
		}
	}
}

//--------------------------------------------------------------

void outputWindowApp::keyPressed(int key) {
	if (key == 'f')
	{
		ofToggleFullscreen();
		isFullscreen = !isFullscreen;
		if (!isFullscreen)
		{
			ofSetWindowShape(640, 360);
			ofSetWindowPosition(100, 100);
		}
	}
}


//--------------------------------------------------------------

void outputWindowApp::setFullscreen()
{
	ofSetWindowPosition(ofGetWindowPositionX() + 50, ofGetWindowPositionY() + 50);
	ofToggleFullscreen();
	isFullscreen = true;
}

//--------------------------------------------------------------

void outputWindowApp::exit()
{
	isRunning = false;
}

//--------------------------------------------------------------

void outputWindowApp::windowResized(int w, int h){
	updateHomography();
	windowSize.x = ofGetWindowWidth();
	windowSize.y = ofGetWindowHeight();
}

//--------------------------------------------------------------

void outputWindowApp::mousePressed(ofMouseEventArgs & args)
{
	clickedCorner = inside(ofPoint(args.x, args.y));
}

//--------------------------------------------------------------

void outputWindowApp::mouseReleased(ofMouseEventArgs & args)
{
	clickedCorner = -1;
}

//--------------------------------------------------------------

void outputWindowApp::mouseMoved(ofMouseEventArgs & args) {}

//--------------------------------------------------------------

void outputWindowApp::mouseDragged(ofMouseEventArgs & args) 
{
	if (clickedCorner > -1)
	{
		if (args.x > 0 && args.x < ofGetWindowWidth()) {
			distortedCorners[clickedCorner].set(args.x / (float)ofGetWindowWidth(), distortedCorners[clickedCorner].y);
		}
		else if (args.x > ofGetWindowWidth()) {
			distortedCorners[clickedCorner].set(1, distortedCorners[clickedCorner].y);
		}
		else if (args.x < 0) {
			distortedCorners[clickedCorner].set(0, distortedCorners[clickedCorner].y);
		}

		if(args.y > 0 && args.y < ofGetWindowHeight()) {
			distortedCorners[clickedCorner].set(distortedCorners[clickedCorner].x, args.y / (float)ofGetWindowHeight());
		}
		else if (args.y > ofGetWindowHeight()) {
			distortedCorners[clickedCorner].set(distortedCorners[clickedCorner].x, 1);
		}
		else if (args.y < 0) {
			distortedCorners[clickedCorner].set(distortedCorners[clickedCorner].x, 0);
		}

		updateHomography();
	}
}

void outputWindowApp::updateHomography()
{
	for (int i = 0; i < 4; i++)
	{
		distortedCornersScreen[i].set(distortedCorners[i].x * ofGetWindowWidth(), distortedCorners[i].y * ofGetWindowHeight());
		originalCornersScreen[i].set(originalCorners[i].x * ofGetWindowWidth(), originalCorners[i].y * ofGetWindowHeight());
	}
	homography = ofxHomography::findHomography(originalCornersScreen, distortedCornersScreen);
}

//--------------------------------------------------------------

void outputWindowApp::mouseScrolled(ofMouseEventArgs & args) {}

//--------------------------------------------------------------

void outputWindowApp::mouseEntered(ofMouseEventArgs & args)
{
	mouseInsideOutputWindowApp = true;
}

//--------------------------------------------------------------

void outputWindowApp::mouseExited(ofMouseEventArgs & args) 
{
	mouseInsideOutputWindowApp = false;
}

//--------------------------------------------------------------

int outputWindowApp::inside(ofPoint mousePos)
{
	for (int i = 0; i < 4; i++)
	{
		if (ofDist(mousePos.x, mousePos.y, distortedCornersScreen[i].x, distortedCornersScreen[i].y) < cornerSize)
			return i;
	}
	return -1;
}

//--------------------------------------------------------------

ofxJSONElement outputWindowApp::getParameters()
{
	ofxJSONElement parameters;
	parameters["ID"] = id;
	

	ofxJSON::Value size(Json::arrayValue);
	size.append(windowSize.x);
	size.append(windowSize.y);
	parameters["Size"] = size;


	ofxJSON::Value position(Json::arrayValue);
	position.append(windowPosition.x);
	position.append(windowPosition.y);
	parameters["Position"] = position;


	ofxJSON::Value homography(Json::arrayValue);
	for (int i = 0; i < 4; i++)
	{
		ofxJSON::Value point(Json::arrayValue);
		point.append(distortedCorners[i].x);
		point.append(distortedCorners[i].y);
		homography.append(point);
	}
	parameters["Homography"] = homography;

	parameters["VideosourceID"] = videosourceID;

	parameters["isFullscreen"] = isFullscreen;

	return parameters;
}