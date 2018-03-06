#pragma once

#include "ofMain.h"
#include "Quad.h"
#include "TreeQuads.h"
//#include "ofxDatGui.h"
#include "ofxGui.h"

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
		void loadSceneFromPath(string path);
		void loadSceneFromPrompt();
		void saveSceneFromPrompt();
		void addQuad();
		void toggleMode();
		void deleteSelected();
		void changeSelectedSource();
		void setSelectedSplit(float & newSplit);
		void stopAnimation();
		void playAnimation();
		void setVideoSpeed(float & newSpeed);
		void setAnimationDuration(float & newDuration);
		void setStartAnimation();
		void setEndAnimation();

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
		vector<shared_ptr<TreeQuad>> trees;

		//ofxDatGuiTextInput* animationDurationInput;
		//ofxDatGuiFolder* selectedQuadFolder;
		//ofxDatGuiSlider * textureSplitSlider;
		//ofxDatGuiSlider * videoSpeedSlider;
		//ofxDatGui* gui;
		ofxPanel newGui;
		ofxLabel fpsLabel;
		ofxLabel sceneLabel;
		ofxLabel selectedQuadLabel;
		ofxButton addQuadButton;
		ofxButton clearSceneButton;
		ofxButton saveSceneButton;
		ofxButton loadSceneButton;
		ofxButton enterPresentationButton;
		ofxGuiGroup selectedQuadControlGroup;
		ofxButton deleteQuadButton;
		ofxButton changeQuadSourceButton;
		ofxFloatSlider quadSplitSlider;
		ofxButton setStartAnimationButton;
		ofxButton setEndAnimationButton;
		ofxFloatSlider animationDurationSlider;
		ofxFloatSlider selectedVideoSpeedSlider;
		ofxButton playAnimationButton;
		ofxButton stopAnimationButton;

};
