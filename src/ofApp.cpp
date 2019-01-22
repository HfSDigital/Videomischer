#include "ofApp.h"

#include "vmCamera.h"
#include "vmPlayer.h"
#include "vmPicture.h"
#include "vmChat.h"
#include "vmAudio.h"

//int preview::previewID = 65;

//--------------------------------------------------------------

void ofApp::setup(){
	
	ofSetFrameRate(60);
	ofSetEscapeQuitsApp(false);
	ofSetWindowTitle("Videomischer");


	ofAddListener(ofGetWindowPtr()->events().keyPressed, this, &ofApp::keycodePressed);
	ofAddListener(ofGetWindowPtr()->events().keyReleased, this, &ofApp::keycodeReleased);
	bCTRLpressed = false;
	bALTpressed = false;
	bSHIFTpressed = false;

	// Load Font

	std_font = make_shared<ofTrueTypeFont>();
	std_font->loadFont("RobotoCondensed-Regular.ttf", 10);
	//std_font->loadFont("LANENAR_.ttf", 10);
	

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


	// Get all audio files and add them to videoSources

	dir.open("audio");
	vector<ofFile> audiofiles = dir.getFiles();
	for (int i = 0; i < audiofiles.size(); i++)
	{
		cout << audiofiles[i].getAbsolutePath() << endl;
		videoSources.push_back(make_shared<vmAudio>(audiofiles[i].getAbsolutePath()));
	}


	// Load stored Session

	if (saveFileElement.open(saveFile))
	{
		// Restore General Settings
		vmSettings.autoSwitchEnabled = saveFileElement["generalSettings"]["autoSwitchEnabled"].asBool();
		vmSettings.autoSwitchInterval = saveFileElement["generalSettings"]["autoSwitchInterval"].asUInt64();
		vmSettings.autoSwitchIntervalRandom = saveFileElement["generalSettings"]["autoSwitchIntervalRandom"].asUInt64();
		vmSettings.footcontrollerEnabled = saveFileElement["generalSettings"]["footcontrollerEnabled"].asBool();
		vmSettings.chatEnabled = saveFileElement["generalSettings"]["chatEnabled"].asBool();
		
		// Add a chat to the videoSources
		if (vmSettings.chatEnabled) {
			videoSources.push_back(make_shared<vmChat>());
		}

		// Restore Size and Position of MainWindow
		windowSize.x = saveFileElement["mainWindow"]["Size"][0].asInt();
		windowSize.y = saveFileElement["mainWindow"]["Size"][1].asInt();
		ofSetWindowShape(windowSize.x, windowSize.y);
		ofSetWindowPosition(saveFileElement["mainWindow"]["Position"][0].asInt(), saveFileElement["mainWindow"]["Position"][1].asInt());

		// Restore OutputWindows
		for (int i = 0; i < saveFileElement["outputWindows"].size(); i++)
		{
			addOutputWindow(
				ofVec2f(saveFileElement["outputWindows"][i]["Size"][0].asInt(),
					saveFileElement["outputWindows"][i]["Size"][1].asInt()),
				ofVec2f(saveFileElement["outputWindows"][i]["Position"][0].asInt(),
					saveFileElement["outputWindows"][i]["Position"][1].asInt()),
				saveFileElement["outputWindows"][i]["ID"].asInt());
			for (int j = 0; j < 4; j++)
			{
				outputWindowApps.back()->distortedCorners[j].x = saveFileElement["outputWindows"][i]["Homography"][j][0].asFloat();
				outputWindowApps.back()->distortedCorners[j].y = saveFileElement["outputWindows"][i]["Homography"][j][1].asFloat();
			}
			//outputWindowApps.back()->setTexture(videoSources[saveFileElement["outputWindows"][i]["VideosourceID"].asInt()]->getTexture());
			outputWindowApps.back()->setTexture(videoSources[0]->getTexture());
			outputWindowApps.back()->videosourceID = 0;// saveFileElement["outputWindows"][i]["VideosourceID"].asInt();
			outputWindowApps.back()->isFullscreen = saveFileElement["outputWindows"][i]["isFullscreen"].asBool();
			if (outputWindowApps.back()->isFullscreen) outputWindowApps.back()->setFullscreen();
		}

		// Restore Preview-Settings, KeyCodes etc
		for (int i = 0; i < saveFileElement["videoSources"].size(); i++) {
			for (shared_ptr<preview> p : previews) {
				if (saveFileElement["videoSources"][i]["title"].asString() == p->videoSource->title) {
					p->videoSource->bLoop = saveFileElement["videoSources"][i]["loop"].asBool();
					p->videoSource->bMute = saveFileElement["videoSources"][i]["mute"].asBool();

					for (int j = 0; j < saveFileElement["videoSources"][i]["keycodes"].size(); j++) {
						if (saveFileElement["videoSources"][i]["keycodes"][j]["outputWindowID"].asInt() == p->outputWindow->id) {
							p->keyboardShortcut = saveFileElement["videoSources"][i]["keycodes"][j]["keycode"].asInt();
						}
					}
				}
			}
		}
	}
	else {
		// Add a chat to the videoSources as standard-option
		if(vmSettings.chatEnabled) videoSources.push_back(make_shared<vmChat>());
	}


	if (outputWindowApps.size() < 1) {
		addOutputWindow(ofVec2f(1280, 720), ofVec2f(50,250), 0);
	}

	lastSwitchTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------

void ofApp::update(){
	
	//std::stringstream strm;
	//strm << "fps: " << ofGetFrameRate();
	//ofSetWindowTitle(strm.str());

	windowPosition.x = ofGetWindowPositionX();
	windowPosition.y = ofGetWindowPositionY();

	// Switch Video automatically
	if (vmSettings.autoSwitchEnabled) {
		uint64_t currentTime = ofGetElapsedTimeMillis();
		if (currentTime > lastSwitchTime + switchInterval) {
			cout << "switching.." << endl;
			int vID = (int)ofRandom(previews.size() / outputWindowApps.size());
			previews.at(vID)->showVideo();
			switchInterval = (int)ofRandom(
								vmSettings.autoSwitchInterval - vmSettings.autoSwitchIntervalRandom / 2, 
								vmSettings.autoSwitchInterval + vmSettings.autoSwitchIntervalRandom / 2
							    );
			cout << "next int	erval: " << vmSettings.autoSwitchInterval << endl;
			lastSwitchTime = currentTime;
		}
	}
	

	// Update all Videosources
	for (int i = 0; i < videoSources.size(); i++) {
		videoSources[i]->update();
	}


//	 Stop a Video if its not shown in any Output Window anymore
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


	// Check if Output-Windows are still running
	for (int i = 0; i < outputWindowApps.size(); i++)
	{
		if (!outputWindowApps[i]->isRunning)
		{
			cout << "---------------" << endl;
			cout << "deleting previews " << previews.size() << endl;
			vector<shared_ptr<preview>>::iterator iter;
			iter = previews.begin();
			while(iter != previews.end())
			{
				shared_ptr<preview> p = *iter;
				if (p->outputWindow->id == outputWindowApps[i]->id)
				{
					iter = previews.erase(iter);
				}
				else {
					iter++;
				}
			}
			cout << "done deleting previews " << previews.size() << endl;

			cout << "erasing outputWindow " << i << "with ID" << outputWindowApps[i]->id << " running?" << outputWindowApps[i]->isRunning << endl;
			outputWindowApps.erase(outputWindowApps.begin() + i);

			arrangePreviews();
		}
	}

}

//--------------------------------------------------------------

void ofApp::draw(){
	ofBackground(33);
	ofScale(globals::guiScale, globals::guiScale);
	// Draw Background for Previews
	//ofPushMatrix();
	//ofPushStyle();
	//for (int i = 0; i < outputWindowApps.size(); i++) {
	//	ofTranslate(0, globals::padding);

	//	ofFill();
	//	ofSetColor(99);
	//	ofRect(0, 0, ofGetWindowWidth(), previews[0]->size.y + globals::padding*3);

	//	ofNoFill();
	//	ofSetColor(ofColor::black);
	//	ofDrawBitmapString("Display: " + to_string(outputWindowApps[i]->id), globals::padding, globals::padding);
	//	
	//	ofTranslate(0, previews[0]->size.y + globals::padding*3);
	//}
	//ofPopStyle();
	//ofPopMatrix();

	showHelp(globals::padding, ofGetWindowHeight() - globals::padding);

	// Draw Previews
	for (int i = 0; i < previews.size(); i++)
	{
		previews[i]->draw();
	}
}

//--------------------------------------------------------------

void ofApp::arrangePreviews() {

	if (outputWindowApps.size() == 0) return;

	int previewsPerGroup = previews.size() / outputWindowApps.size();
	int w = mainWindow->getWidth();
	int p = globals::padding;

	ofVec2f thumbnailSize;
	thumbnailSize.x = globals::thumnailSizeMin;
	
	int previewsPerRow = float(w - p) / float(thumbnailSize.x + p);
	if (previewsPerRow > previewsPerGroup) previewsPerRow = previewsPerGroup;

	int previewRowsPerGroup = ((float)(previewsPerGroup-1) / (float)previewsPerRow) + 1;

	thumbnailSize.x = (float(w - p) / float(previewsPerRow)) - p;
	thumbnailSize.x = ofClamp(thumbnailSize.x, globals::thumnailSizeMin, globals::thumnailSizeMax);
	thumbnailSize.y = (float)thumbnailSize.x / 16.0f * 9.0f;
	
	for (int i = 0; i < previews.size(); i++) {
		previews[i]->setSize(thumbnailSize);
		previews[i]->trimTitle();
		previews[i]->std_font = this->std_font;

		
		int currentGroup = i / previewsPerGroup;
		int currentItem = i % previewsPerGroup;
		//cout << "i: " << i << "\tcurrent group: " << currentGroup << "\tcurrentItem: " << currentItem << endl;

		ofVec2f pos;
		pos.x = currentItem % previewsPerRow * thumbnailSize.x;
		pos.x += p
					+ p * (currentItem % previewsPerRow);		// add space between thumbnails

		pos.y = currentItem / previewsPerRow * thumbnailSize.y + (currentGroup * previewRowsPerGroup * thumbnailSize.y);
		pos.y += 2 * p 
					+ p * currentGroup * 4
					+ p * (currentItem / previewsPerRow);

		previews[i]->setPos(pos);
	}
}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h)
{
	arrangePreviews();
	windowSize.x = ofGetWindowWidth();
	windowSize.y = ofGetWindowHeight();
}

//--------------------------------------------------------------

void ofApp::showHelp(int x, int y) {
	int lines = 5;
	stringstream help;
	help << "[CTRL] + [SHIFT] + F:	 Enter/Exit Fullscreen (first click on the window you want to maximize)" << endl;
	help << "[CTRL] + [SHIFT] + [+]: Add a Output Window" << endl;
	help << "[CTRL] + [SHIFT] + Q:	 Quit" << endl;
	help << "Chat:" << endl;
	help << "Press [1] or [2] to switch between chat partners. Hint: Use two keyboards on/off stage!" << endl;

	ofSetColor(ofColor::gray);
	std_font->drawString(help.str(), x, y - std_font->getLineHeight() * (lines-1));
}

//--------------------------------------------------------------

//void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------

void ofApp::keycodePressed(ofKeyEventArgs& e) {
	if (vmSettings.footcontrollerEnabled) {
		int nextClipID = 0;
		if (e.keycode == 49) {
  		    // play previous clip 

			if (outputWindowApps[0]->videosourceID > 0)
				nextClipID = outputWindowApps[0]->videosourceID - 1;

			previews.at(nextClipID)->showVideo();
		}
		else if (e.keycode == 50) {		
			// play next clip

			if (outputWindowApps[0]->videosourceID < previews.size())
				nextClipID = outputWindowApps[0]->videosourceID + 1;

			previews.at(nextClipID)->showVideo();
		}
	}
	if (e.keycode == 340) {			// Shift Key
		bSHIFTpressed = true;
	}
	else if (e.keycode == 341) {	// Ctrl Key
		bCTRLpressed = true;
	}
	else if (e.keycode == 342) {	// Alt Key
		bALTpressed = true;
	}
	else if (e.keycode == 32) {	// SPACE Key
		for (int i = 0; i < outputWindowApps.size(); i++) {
			previews.at(outputWindowApps[i]->videosourceID)->videoSource->pause();
		}
	}
	else if (e.keycode != 0) {
		if (bCTRLpressed && !bSHIFTpressed) {
			for (int i = 0; i < previews.size(); i++) {
				if (e.keycode == previews.at(i)->keyboardShortcut) {
					// show and play preview
					previews.at(i)->showVideo();
				}
			}
		}
		else if (bCTRLpressed && bSHIFTpressed)
		{
			if (e.keycode == 81) {
				cout << "goodbye, hope you had fun!" << endl;
				exit();
			}
			else if (e.keycode == 93)		// + Key
			{
				addOutputWindow(ofVec2f(640, 360), ofVec2f(100, 100));
			}
		}
		else {
			for (int i = 0; i < previews.size(); i++) {
				if (previews.at(i)->waitForKey) {
					previews.at(i)->keyboardShortcut = e.keycode;
					previews.at(i)->waitForKey = false;
				}
			}
			for (int i = 0; i < outputWindowApps.size(); i++) {
				if (videoSources.at(outputWindowApps.at(i)->videosourceID)->title == "chat") {
					videoSources.at(outputWindowApps.at(i)->videosourceID)->receiveKeyInput(e.key);
				}
			}
		}
	}
}

//--------------------------------------------------------------

void ofApp::keycodeReleased(ofKeyEventArgs& e) {
	if (e.keycode == 340) {			// Shift Key
		bSHIFTpressed = false;
	}
	else if (e.keycode == 341) {		// Ctrl Key
		bCTRLpressed = false;
	}
	else if (e.keycode == 342) {		// Alt Key
		bALTpressed = false;
	}
}

//--------------------------------------------------------------

void ofApp::addOutputWindow(ofVec2f size, ofVec2f position, int id)
{
	if(id > -1)
		outputWindowApps.push_back(make_shared<outputWindowApp>(id));
	else
		outputWindowApps.push_back(make_shared<outputWindowApp>());

	outputWindowApps.back()->setTexture(videoSources[0]->getTexture());

	// Add previews
	for (int j = 0; j < videoSources.size(); j++)
	{
		previews.push_back(make_shared<preview>(outputWindowApps.back(), videoSources[j], std_font));
	}

	arrangePreviews();

	// Create Window and run App
	ofGLFWWindowSettings settings;
	settings.shareContextWith = mainWindow;
	settings.width = ofClamp(size.x, 100, 3000);
	settings.height = ofClamp(size.y, 100, 3000);
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 50;
	settings.setPosition(position);

	settings.title = "output window #" + to_string(outputWindowApps.back()->id);
	shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
	ofRunApp(window, outputWindowApps.back());
	outputWindowApps.back()->_mainApp = this;
}

//--------------------------------------------------------------

void ofApp::exit()
{
	// Output Windows
	ofxJSON::Value windows(Json::arrayValue);
	for (int i = 0; i < outputWindowApps.size(); i++)
	{
		windows.append(ofxJSON::Value(outputWindowApps[i]->getParameters()));
	}
	saveFileElement["outputWindows"] = windows;


	// Main Window
	ofxJSONElement mainWindowParameters;

	ofxJSON::Value size(Json::arrayValue);
	size.append(windowSize.x);
	size.append(windowSize.y);
	mainWindowParameters["Size"] = size;

	ofxJSON::Value position(Json::arrayValue);
	position.append(windowPosition.x);
	position.append(windowPosition.y);
	mainWindowParameters["Position"] = position;

	saveFileElement["mainWindow"] = mainWindowParameters;


	// Video Sources 
	ofxJSONElement videosources;

	for (int i = 0; i < videoSources.size(); i++) {
		ofxJSONElement videosourceParameters;
		videosourceParameters["title"] = previews.at(i)->videoSource->title;
		videosourceParameters["mute"] = previews.at(i)->videoSource->bMute;
		videosourceParameters["loop"] = previews.at(i)->videoSource->bLoop;


		ofxJSONElement keyCodes;
		for (int j = 0; j < outputWindowApps.size(); j++)
		{
			ofxJSONElement keycodeInOutputWindow;
			keycodeInOutputWindow["outputWindowID"] = outputWindowApps[j]->id;
			keycodeInOutputWindow["keycode"] = previews.at(i + j * videoSources.size())->keyboardShortcut;
			keyCodes[j] = keycodeInOutputWindow;
		}
		videosourceParameters["keycodes"] = keyCodes;

		videosources[i] = videosourceParameters;
	}	
	saveFileElement["videoSources"] = videosources;


	// General Settings
	ofxJSONElement generalSettings;
	generalSettings["chatEnabled"] = vmSettings.chatEnabled;
	generalSettings["autoSwitchEnabled"] = vmSettings.autoSwitchEnabled;
	generalSettings["autoSwitchInterval"] = vmSettings.autoSwitchInterval;
	generalSettings["autoSwitchIntervalRandom"] = vmSettings.autoSwitchIntervalRandom;
	generalSettings["footcontrollerEnabled"] = vmSettings.footcontrollerEnabled;

	saveFileElement["generalSettings"] = generalSettings;


	// save JSON File
	saveFileElement.save(saveFile, true);


	OF_EXIT_APP(0);
}

//--------------------------------------------------------------

void ofApp::mouseMoved(ofMouseEventArgs & args) {
	for (int i = 0; i < previews.size(); i++)
	{
		previews[i]->inside(args.x, args.y);
	}
};

//--------------------------------------------------------------

void ofApp::mousePressed(ofMouseEventArgs & args) {
	for (int i = 0; i < previews.size(); i++)
	{
		previews[i]->inside(args.x, args.y, true);
	}
};

//--------------------------------------------------------------

void ofApp::mouseDragged(ofMouseEventArgs & args) {};
void ofApp::mouseReleased(ofMouseEventArgs & args) {};
void ofApp::mouseScrolled(ofMouseEventArgs & args) {};
void ofApp::mouseEntered(ofMouseEventArgs & args) {};
void ofApp::mouseExited(ofMouseEventArgs & args) {};
