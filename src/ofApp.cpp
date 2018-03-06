#include "ofApp.h"
//#include "GuiTheme.h"
#include "./MediaSource/ImageSource.h"
#include "./MediaSource/VideoSource.h"
#include "regex"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);

	ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
	
	//gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
	//gui->setTheme(new GuiTheme());
	//gui->addHeader(":: Menu ::");
	//gui->addButton("Add Quad");
	//gui->addButton("Clear All Quads");
	//gui->addButton("Save Scene");
	//gui->addButton("Load Scene");
	//gui->addButton("Enter Presentation Mode");
	//gui->addBreak();
	//selectedQuadFolder = gui->addFolder("Selected Quad", ofColor::black);
	//selectedQuadFolder->addButton("Delete");
	//selectedQuadFolder->addButton("Change Source");
	//textureSplitSlider = selectedQuadFolder->addSlider("Texture Split", 0, 1);
	//selectedQuadFolder->addButton("Set Start Animation");
	//selectedQuadFolder->addButton("Set End Animation");
	//animationDurationInput = selectedQuadFolder->addTextInput("Animation Duration (m)", "30");
	//animationDurationInput->setInputType(ofxDatGuiInputType::NUMERIC);
	//videoSpeedSlider = selectedQuadFolder->addSlider("Video Speed", 0, 5);
	//videoSpeedSlider->setValue(1);
	//selectedQuadFolder->addButton("Play Animation");
	//selectedQuadFolder->addButton("Stop Animation");
	//selectedQuadFolder->expand();
	//gui->addBreak();
	//ofxDatGuiFolder* hotkeyFolder = gui->addFolder("Hotkeys", ofColor::white);
	//hotkeyFolder->addLabel("p to enter presentation mode");
	//hotkeyFolder->addLabel("m to enter mapping mode");
	//hotkeyFolder->addLabel("f to toggle fullscreen");
	//hotkeyFolder->expand();
	//gui->addFRM();
	//gui->addFooter();


	//gui->onSliderEvent([&](ofxDatGuiSliderEvent e)
	//{
	//	if (e.target->is("Texture Split")) {
	//		selectedTree->setTextureSplit(e.value);
	//	}
	//	else if (e.target->is("Video Speed")) {
	//		if (selectedTree->getSource()->getType() == SourceType::video) {
	//			VideoSource * source = dynamic_cast<VideoSource*>(selectedTree->getSource());
	//			source->setSpeed(e.value);
	//		}
	//	}
	//});
	//gui->onTextInputEvent([&](ofxDatGuiTextInputEvent e)
	//{
	//	if (e.target->is("Animation Duration (m)")) {
	//		float duration = ofToFloat(e.text);
	//		selectedTree->setAnimationDuration(duration * 60);
	//	}
	//});
	//gui->onButtonEvent([&](ofxDatGuiButtonEvent e)
	//{
	//	if (e.target->is("Add Quad")) {
	//		ofFileDialogResult result = ofSystemLoadDialog("Load image or movie file", false, ofToDataPath(".", true));
	//		if (result.bSuccess) {
	//			string path = result.getPath();

	//			regex imageExtensions("(gif|jpg|jpeg|tiff|png|bmp)$", regex_constants::icase);
	//			regex videoExtensions("(mov|avi|wmv|flv|mp4)$", regex_constants::icase);

	//			BaseSource * source;
	//			if (regex_search(path, imageExtensions)) {
	//				source = new ImageSource(path);
	//			}
	//			else if (regex_search(path, videoExtensions)) {
	//				source = new VideoSource(path);
	//			}
	//			else {
	//				throw std::string("Unrecognized file format: " + path);
	//			}

	//			shared_ptr<TreeQuad> tree (new TreeQuad(0, 0, source, 0.8));
	//			trees.push_back(tree);
	//			selectTree(tree);
	//		}
	//	}
	//	else if (e.target->is("Delete")) {
	//		if (selectedTree) {
	//			for (int i = 0; i < trees.size(); i++) {
	//				if (trees[i] == selectedTree) {
	//					trees.erase(trees.begin() + i);
	//					selectedTree = nullptr;
	//				}
	//			}
	//		}
	//	}
	//	else if (e.target->is("Change Source")) {
	//		ofFileDialogResult result = ofSystemLoadDialog("Load image or movie file", false, ofToDataPath(".", true));
	//		if (result.bSuccess) {
	//			string path = result.getPath();

	//			regex imageExtensions("(gif|jpg|jpeg|tiff|png|bmp)$", regex_constants::icase);
	//			regex videoExtensions("(mov|avi|wmv|flv|mp4)$", regex_constants::icase);

	//			BaseSource * source;
	//			if (regex_search(path, imageExtensions)) {
	//				source = new ImageSource(path);
	//			}
	//			else if (regex_search(path, videoExtensions)) {
	//				source = new VideoSource(path);
	//			}
	//			else {
	//				throw std::string("Unrecognized file format: " + path);
	//			}

	//			selectedTree->setSource(source);
	//		}
	//	}
	//	else if (e.target->is("Set Start Animation")) {
	//		if (selectedTree) {
	//			selectedTree->setAnimationStartShape();
	//		}
	//	}
	//	else if (e.target->is("Set End Animation")) {
	//		if (selectedTree) {
	//			selectedTree->setAnimationEndShape();
	//		}
	//	}
	//	else if (e.target->is("Play Animation")) {
	//		if (selectedTree) {
	//			selectedTree->playAnimation();
	//		}
	//	}
	//	else if (e.target->is("Stop Animation")) {
	//		if (selectedTree) {
	//			selectedTree->stopAnimation();
	//		}
	//	}
	//	else if (e.target->is("Save Scene")) {
	//		ofFileDialogResult result = ofSystemSaveDialog("scene.xml", "Save");
	//		if (result.bSuccess) {
	//			saveScene(result.getPath());
	//		}
	//	}
	//	else if (e.target->is("Load Scene")) {
	//		ofFileDialogResult result = ofSystemLoadDialog("Load an xml scene file", false, ofToDataPath(".", true));
	//		if (result.bSuccess) {
	//			loadScene(result.getPath());
	//		}
	//	}
	//	else if (e.target->is("Clear All Quads")) {
	//		clearScene();
	//	}
	//	else if (e.target->is("Enter Presentation Mode")) {
	//		setMode(ApplicationMode::presentation);
	//	}
	//});

	bool validSettings = xmlSettings.load("settings.xml") && xmlSettings.exists("settings");
	xmlSettings.setTo("settings");
	if (xmlSettings.exists("lastLoadedScenePath")) {
		cout << "loaded found" << endl;
		loadScene(xmlSettings.getValue("lastLoadedScenePath"));
	}
	else if (xmlSettings.exists("lastSavedScenePath")) {
		cout << "saved found" << endl;
		loadScene(xmlSettings.getValue("lastSavedScenePath"));
	}
	else {
		cout << "No settings found" << endl;
		xmlSettings.clear();
		xmlSettings.addChild("settings");
		xmlSettings.setTo("settings");
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	//selectedQuadFolder->setVisible(selectedTree != nullptr);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);

	for (int i = 0; i < trees.size(); i++) {
		trees[i]->draw();
	}
}

void ofApp::setMode(ApplicationMode newMode) {
	this->mode = newMode;
	if (this->mode == ApplicationMode::presentation) {
		mode = ApplicationMode::presentation;
		//gui->setVisible(false);
		for (int i = 0; i < trees.size(); i++) {
			trees[i]->disableInput();
			trees[i]->playAnimation();
		}
	}
	else if (this->mode == ApplicationMode::mapping) {
		mode = ApplicationMode::mapping;
		//gui->setVisible(true);
		for (int i = 0; i < trees.size(); i++) {
			trees[i]->enableInput();
			trees[i]->stopAnimation();
		}
	}
}

void ofApp::selectTree(shared_ptr<TreeQuad> tree) {
	tree->enableInput();
	selectedTree = tree;
	//animationDurationInput->setText(ofToString(selectedTree->getAnimationDuration() / 60));
	for (int i = 0; i < trees.size(); i++) {
		if (trees[i] != tree) {
			trees[i]->disableInput();
		}
	}
}

void ofApp::clearScene() {
	trees.clear();
}

void ofApp::loadScene(string path)
{
	clearScene();

	ofXml xml;
	if (xml.load(path)) {
		xml.setTo("scene");
		xml.setTo("trees");
		int numTrees = xml.getNumChildren();
		for (int i = 0; i < numTrees; i++) {
			xml.setTo("tree[" + ofToString(i) + "]");
			shared_ptr<TreeQuad> tree(new TreeQuad());
			tree->loadFromXml(xml);
			trees.push_back(tree);
			xml.setToParent();
		}

		string relativePath = ofFilePath::isAbsolute(path) ? ofFilePath::makeRelative(ofToDataPath("./", true), path) : path;
		if (xmlSettings.exists("lastLoadedScenePath")) {
			xmlSettings.setValue("lastLoadedScenePath", relativePath);
		}
		else {
			xmlSettings.addValue("lastLoadedScenePath", relativePath);
		}
		xmlSettings.save("settings.xml");
	}
}

void ofApp::saveScene(string path)
{
	if (path.compare(path.length() - 4, 4, ".xml") != 0) {
		path += ".xml";
	}
	xmlScene.clear();
	xmlScene.addChild("scene");
	xmlScene.setTo("scene");
	xmlScene.addChild("trees");
	xmlScene.setTo("trees");
	for (int i = 0; i < trees.size(); i++) {
		ofXml treeXml = trees[i]->saveToXml();
		xmlScene.addXml(treeXml, true);
	}
	xmlScene.save(path);

	string relativePath = ofFilePath::isAbsolute(path) ? ofFilePath::makeRelative(ofToDataPath("./", true), path) : path;

	if (xmlSettings.exists("lastSavedScenePath")) {
		xmlSettings.setValue("lastSavedScenePath", relativePath);
	}
	else {
		xmlSettings.addValue("lastSavedScenePath", relativePath);
	}
	xmlSettings.save("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'f') ofToggleFullscreen();
	else if (key == 'p') setMode(ApplicationMode::presentation);
	else if (key == 'm') setMode(ApplicationMode::mapping);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (mode == ApplicationMode::presentation) return;
	for (int i = 0; i < trees.size(); i++) {
		if (trees[i]->isPointInside(ofVec2f(x, y))) {
			selectTree(trees[i]);
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


//ofMesh subdividedQuad;
//
//float width = 200;
//float height = 200;
//float numSubdivisions = 10;
//for (int row = 0; row < numSubdivisions; row++) {
//	ofVec2f left(
//		ofMap(row, 0, numSubdivisions, topLeft.x, bottomLeft.x),
//		ofMap(row, 0, numSubdivisions, topLeft.y, bottomLeft.y)
//	);
//	ofVec2f right(
//		ofMap(row, 0, numSubdivisions, topRight.x, bottomRight.x),
//		ofMap(row, 0, numSubdivisions, topRight.y, bottomRight.y)
//	);
//	for (int col = 0; col < numSubdivisions; col++) {
//		float x = ofMap(col, 0, numSubdivisions, left.x, right.x);
//		float y = ofMap(col, 0, numSubdivisions, left.y, right.y);
//		subdividedQuad.addVertex(ofVec3f(x, y, 1));
//		subdividedQuad.addTexCoord(ofVec2f(col / numSubdivisions * image.getWidth(), row / numSubdivisions * image.getHeight()));
//	}
//}
//
//for (int y = 0; y < numSubdivisions - 1; y++) {
//	for (int x = 0; x < numSubdivisions - 1; x++) {
//		subdividedQuad.addIndex(x + y * numSubdivisions);         // 0
//		subdividedQuad.addIndex((x + 1) + y * numSubdivisions);     // 1
//		subdividedQuad.addIndex(x + (y + 1) * numSubdivisions);     // 10
//
//		subdividedQuad.addIndex((x + 1) + y * numSubdivisions);     // 1
//		subdividedQuad.addIndex((x + 1) + (y + 1) * numSubdivisions); // 11
//		subdividedQuad.addIndex(x + (y + 1) * numSubdivisions);     // 10
//	}
//}