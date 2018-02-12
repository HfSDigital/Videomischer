#include "ofApp.h"

#include "vmCamera.h"
#include "vmPlayer.h"
#include "vmPicture.h"


//--------------------------------------------------------------

void ofApp::setup(){
	
	// Get all Pictures and add them to videoSources

	ofDirectory dir("pictures");
	vector<ofFile> picturefiles = dir.getFiles();
	for (int i = 0; i < picturefiles.size(); i++)
	{
		cout << picturefiles[i].getAbsolutePath() << endl;
		videoSources.push_back(make_shared<vmPicture>(picturefiles[i].getAbsolutePath()));
	}



	// Get all Camera-Devices and add them to videoSources

	shared_ptr<ofVideoGrabber> vg = make_shared<ofVideoGrabber>();
	
	int vgCount = vg->listDevices().size();

	for (int i = 0; i < vgCount; i++)
	{
		videoSources.push_back(make_shared<vmCamera>(i));
	}



	// Get all Videos and add them to videoSources

	dir.open("videos");
	vector<ofFile> videofiles = dir.getFiles();
	for (int i = 0; i < videofiles.size(); i++) 
	{
		cout << videofiles[i].getAbsolutePath() << endl;
		videoSources.push_back(make_shared<vmPlayer>(videofiles[i].getAbsolutePath()));
	}



	// Create Previews
	for (int i = 0; i < outputWindowApps.size(); i++) 
	{
		for (int j = 0; j < videoSources.size(); j++)
		{
			previews.push_back(make_shared<preview>(outputWindowApps[i], videoSources[j]));
			//ofAddListener(previews.back()->clickedInside, this, &ofApp::onMouseClickedInPreview);
		}
	}

	arrangePreviews();

	outputWindowApps[0]->setTexture(videoSources[0]->getTexture());
	outputWindowApps[1]->setTexture(videoSources[0]->getTexture());
	outputWindowApps[2]->setTexture(videoSources[0]->getTexture());
}

//--------------------------------------------------------------

void ofApp::update(){
	for (int i = 0; i < videoSources.size(); i++) {
		videoSources[i]->update();
	}

	for (int i = 0; i < videoSources.size(); i++) {
		int stopVideo = true;
		for (int j = 0; j < outputWindowApps.size(); j++) {
			if (videoSources[i]->getTexture() == outputWindowApps[j]->outTexture) 
			{
				stopVideo = false;
			}
		}
		if (stopVideo)
		{
			videoSources[i]->stop();
		}
	}
}

//--------------------------------------------------------------

void ofApp::draw(){
	ofBackground(33);

	// Draw Background for Previews
	ofPushMatrix();
	ofPushStyle();
	for (int i = 0; i < outputWindowApps.size(); i++) {
		ofTranslate(0, globals::padding);

		ofFill();
		ofSetColor(99);
		ofRect(0, 0, ofGetWindowWidth(), previews[0]->size.y + globals::padding*3);

		ofNoFill();
		ofSetColor(ofColor::black);
		ofDrawBitmapString("Display: " + to_string(i), globals::padding, globals::padding);
		
		ofTranslate(0, previews[0]->size.y + globals::padding*3);
	}
	ofPopStyle();
	ofPopMatrix();

	// Draw Previews
	for (int i = 0; i < previews.size(); i++)
	{
		previews[i]->draw();
	}
}

//--------------------------------------------------------------

//void ofApp::onMouseClickedInPreview(int e)
//{
//
//}


//--------------------------------------------------------------

void ofApp::arrangePreviews() {
	int outputWindowCount = outputWindowApps.size();
	int rowCount = previews.size() / outputWindowCount;

	float width = (ofGetWindowWidth() - (rowCount + 1) * globals::padding) / rowCount;
	float height = (float)width / 16.0f * 9.0f;
	ofVec2f size(width, height);

	for (int i = 0; i < previews.size(); i++) {
		previews[i]->setSize(size);
		previews[i]->trimTitle();
		previews[i]->setPos(ofVec2f(previews[i]->videoSource->id  * (width  + globals::padding) + globals::padding, 
									previews[i]->outputWindow->id * (height + globals::padding * 4) + globals::padding * 3));
	}
}