#pragma once

#include "ofMain.h"
#include "Quad.h"
#include "TreeQuads.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	enum class ApplicationMode {
		mapping, presentation
	};

	public:
		void setup();
		void update();
		void draw();

		void setMode(ApplicationMode newMode);
		void selectTree(shared_ptr<TreeQuad> tree);
		void clearScene();
		void loadScene(string path);
		void saveScene(string path);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ApplicationMode mode = ApplicationMode::mapping;

		ofXml xmlScene;
		ofXml xmlSettings;

		shared_ptr<TreeQuad> selectedTree;
		ofxDatGuiTextInput* animationDurationInput;
		ofxDatGuiFolder* selectedQuadFolder;
		ofxDatGuiSlider * textureSplitSlider;
		ofxDatGuiSlider * videoSpeedSlider;

		vector<shared_ptr<TreeQuad>> trees;

		ofxDatGui* gui;
};
