#include "ofApp.h"

#include "vmCamera.h"
#include "vmPlayer.h"
#include "vmPicture.h"


//--------------------------------------------------------------

void ofApp::setup(){
	//ofSetFrameRate(60);

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



	// Load Font

	std_font = make_shared<ofTrueTypeFont>();
	std_font->loadFont("RobotoCondensed-Regular.ttf", 16);




	// Load saved Session

	if (saveFileElement.open(saveFile))
	{
		// Restore Size and Position of MainWindow
		ofSetWindowShape(saveFileElement["mainWindow"]["Size"][0].asInt(), saveFileElement["mainWindow"]["Size"][1].asInt());
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
			outputWindowApps.back()->setTexture(videoSources[saveFileElement["outputWindows"][i]["VideosourceID"].asInt()]->getTexture());
			outputWindowApps.back()->videosourceID = saveFileElement["outputWindows"][i]["VideosourceID"].asInt();
			outputWindowApps.back()->isFullscreen = saveFileElement["outputWindows"][i]["isFullscreen"].asBool();
			if (outputWindowApps.back()->isFullscreen) outputWindowApps.back()->setFullscreen();
		}
	}
}



//--------------------------------------------------------------



void ofApp::update(){

	std::stringstream strm;
	strm << "fps: " << ofGetFrameRate();
	ofSetWindowTitle(strm.str());

	windowPosition.x = ofGetWindowPositionX();
	windowPosition.y = ofGetWindowPositionY();

	// Update all Videosources
	for (int i = 0; i < videoSources.size(); i++) {
		videoSources[i]->update();
	}


	// Stop a Video if its not shown in any Output Window anymore
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
		ofDrawBitmapString("Display: " + to_string(outputWindowApps[i]->id), globals::padding, globals::padding);
		
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

	if (outputWindowApps.size() == 0) return;

	int rowCount = previews.size() / outputWindowApps.size();

	int w = mainWindow->getWidth(); //ofGetWindowWidth();
	float width = (w - (rowCount + 1) * globals::padding) / rowCount;
	width = ofClamp(width, 20, w / 6 + globals::padding);
	float height = (float)width / 16.0f * 9.0f;
	ofVec2f size(width, height);

	for (int i = 0; i < previews.size(); i++) {
		previews[i]->setSize(size);
		previews[i]->trimTitle();
		previews[i]->std_font = this->std_font;
		previews[i]->setPos(ofVec2f(previews[i]->videoSource->id  * (width  + globals::padding) + globals::padding, 
									i/rowCount * (height + globals::padding * 4) + globals::padding * 3));
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

void ofApp::keyPressed(int key)
{
	if (key == GLFW_KEY_SPACE)
	{
		cout << "spACE" << endl;
	}
	if (key == '+')
	{
		addOutputWindow(ofVec2f(640, 360), ofVec2f(100, 100));

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
	settings.width = size.x;
	settings.height = size.y;
	settings.setPosition(position);

	settings.title = "output window #" + to_string(outputWindowApps.back()->id);
	shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
	ofRunApp(window, outputWindowApps.back());

}

//--------------------------------------------------------------

void ofApp::exit()
{
	ofxJSON::Value windows(Json::arrayValue);
	for (int i = 0; i < outputWindowApps.size(); i++)
	{
		windows.append(ofxJSON::Value(outputWindowApps[i]->getParameters()));
	}
	saveFileElement["outputWindows"] = windows;

	ofxJSONElement parameters;

	ofxJSON::Value size(Json::arrayValue);
	size.append(windowSize.x);
	size.append(windowSize.y);
	parameters["Size"] = size;

	ofxJSON::Value position(Json::arrayValue);
	position.append(windowPosition.x);
	position.append(windowPosition.y);
	parameters["Position"] = position;

	saveFileElement["mainWindow"] = parameters;
	saveFileElement.save(saveFile, true);

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
