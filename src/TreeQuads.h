#pragma once

#include "ofMain.h"
#include "Quad.h"
#include "ofxAnimatableFloat.h"
#include "./MediaSource/BaseSource.h"

class TreeQuad
{
	enum class Selection { 
		topLeftVertex, topRightVertex, middleLeftVertex, middleRightVertex, bottomLeftVertex, bottomRightVertex, 
		topEdge, topLeftEdge, bottomLeftEdge, topRightEdge, bottomRightEdge, bottomEdge, middleEdge,
		wholeShape, 
		none 
	};

	public:
		TreeQuad(float x, float y, BaseSource * source, float textureSplitFraction);
		TreeQuad();
		~TreeQuad();
		void enableInput();
		void disableInput();
		void draw();
		ofXml saveToXml(string name = "tree");
		void loadFromXml(ofXml& xml);
		bool isPointInside(ofVec2f pos);
		bool isInputEnabled();
		void setAnimationStartShape();
		void setAnimationEndShape();
		void playAnimation();
		void stopAnimation();
		void setSource(BaseSource * newSource);
		void setAnimationDuration(float seconds);
		float getAnimationDuration();
		void setTextureSplit(float fraction);
		BaseSource* getSource();

	private:
		void onMousePressed(ofMouseEventArgs & mouseArgs);
		void onMouseMoved(ofMouseEventArgs & mouseArgs);
		void onMouseDragged(ofMouseEventArgs & mouseArgs);
		void onMouseReleased(ofMouseEventArgs & mouseArgs);
		void updateAnimation(ofEventArgs& args);
		void moveSelection(ofVec2f delta);
		void setShapeFromAnimation(float animationFraction);

		BaseSource * source;
		bool isAnimating = false;
		ofxAnimatableFloat animationProgress;
		Quad startTopQuad;
		Quad endTopQuad;
		Quad startBottomQuad;
		Quad endBottomQuad;
		float animationDurationSeconds = 30 * 60;
		float animationStartTime = 0;
		bool inputEnabled = false;
		Quad topQuad;
		Quad bottomQuad;
		bool wholeTreeSelected = false;
		Selection currentSelection = Selection::none;
		float selectionDistance = 6;
};

