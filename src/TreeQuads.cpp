#include "TreeQuads.h"
#include "./MediaSource/ImageSource.h"
#include "./MediaSource/VideoSource.h"

TreeQuad::TreeQuad(float x, float y, BaseSource * source, float textureSplitFraction)
{
	this->source = source;
	setTextureSplit(textureSplitFraction);
}

TreeQuad::TreeQuad()
{
	topQuad.setTexCoordsFromRect(ofRectangle());
	topQuad.setVetricesFromRect(ofRectangle());
	bottomQuad.setTexCoordsFromRect(ofRectangle());
	bottomQuad.setVetricesFromRect(ofRectangle());
}

TreeQuad::~TreeQuad()
{
	delete source;
	disableInput();
	stopAnimation();
}

void TreeQuad::enableInput()
{
	if (!inputEnabled) {
		ofAddListener(ofEvents().mouseMoved, this, &TreeQuad::onMouseMoved);
		ofAddListener(ofEvents().mousePressed, this, &TreeQuad::onMousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &TreeQuad::onMouseReleased);
		ofAddListener(ofEvents().mouseDragged, this, &TreeQuad::onMouseDragged);
		inputEnabled = true;
	}
}

void TreeQuad::disableInput()
{
	if (inputEnabled) {
		ofRemoveListener(ofEvents().mouseMoved, this, &TreeQuad::onMouseMoved);
		ofRemoveListener(ofEvents().mousePressed, this, &TreeQuad::onMousePressed);
		ofRemoveListener(ofEvents().mouseReleased, this, &TreeQuad::onMouseReleased);
		ofRemoveListener(ofEvents().mouseDragged, this, &TreeQuad::onMouseDragged);
		inputEnabled = false;
	}
}

void TreeQuad::onMousePressed(ofMouseEventArgs & mouseArgs)
{
	if (mouseArgs.button != 0) return;

	wholeTreeSelected = false;
	currentSelection = Selection::none;

	if (mouseArgs.distance(topQuad.getTopLeft()) <= selectionDistance) currentSelection = Selection::topLeftVertex;
	if (mouseArgs.distance(topQuad.getTopRight()) <= selectionDistance) currentSelection = Selection::topRightVertex;
	if (mouseArgs.distance(topQuad.getBottomLeft()) <= selectionDistance) currentSelection = Selection::middleLeftVertex;
	if (mouseArgs.distance(topQuad.getBottomRight()) <= selectionDistance) currentSelection = Selection::middleRightVertex;
	if (mouseArgs.distance(bottomQuad.getBottomLeft()) <= selectionDistance) currentSelection = Selection::bottomLeftVertex;
	if (mouseArgs.distance(bottomQuad.getBottomRight()) <= selectionDistance) currentSelection = Selection::bottomRightVertex;

	if (mouseArgs.distance(topQuad.getTopMidpoint()) <= selectionDistance) currentSelection = Selection::topEdge;
	if (mouseArgs.distance(topQuad.getLeftMidpoint()) <= selectionDistance) currentSelection = Selection::topLeftEdge;
	if (mouseArgs.distance(bottomQuad.getLeftMidpoint()) <= selectionDistance) currentSelection = Selection::bottomLeftEdge;
	if (mouseArgs.distance(topQuad.getRightMidpoint()) <= selectionDistance) currentSelection = Selection::topRightEdge;
	if (mouseArgs.distance(bottomQuad.getRightMidpoint()) <= selectionDistance) currentSelection = Selection::bottomRightEdge;
	if (mouseArgs.distance(topQuad.getBottomMidpoint()) <= selectionDistance) currentSelection = Selection::middleEdge;
	if (mouseArgs.distance(bottomQuad.getBottomMidpoint()) <= selectionDistance) currentSelection = Selection::bottomEdge;

	if (currentSelection == Selection::none && (topQuad.isPointInside(mouseArgs) || bottomQuad.isPointInside(mouseArgs))) {
		currentSelection = Selection::wholeShape;
	}

	if (currentSelection != Selection::none) {
		ofVec2f delta(mouseArgs.x - ofGetPreviousMouseX(), mouseArgs.y - ofGetPreviousMouseY());
		moveSelection(delta);
	}
}

void TreeQuad::onMouseMoved(ofMouseEventArgs & mouseArgs)
{
	if (currentSelection != Selection::none) {
		ofVec2f delta(mouseArgs.x - ofGetPreviousMouseX(), mouseArgs.y - ofGetPreviousMouseY());
		moveSelection(delta);
	}
}

void TreeQuad::onMouseDragged(ofMouseEventArgs & mouseArgs)
{
	if (currentSelection != Selection::none) {
		ofVec2f delta(mouseArgs.x - ofGetPreviousMouseX(), mouseArgs.y - ofGetPreviousMouseY());
		moveSelection(delta);
	}
}

void TreeQuad::onMouseReleased(ofMouseEventArgs & mouseArgs)
{
	currentSelection = Selection::none;
}

void TreeQuad::moveSelection(ofVec2f delta)
{
	switch (currentSelection)
	{
		case Selection::wholeShape:
			topQuad.translate(delta);
			bottomQuad.translate(delta);
			break;
		case Selection::topLeftVertex:
			topQuad.translateTopLeft(delta);
			break;
		case Selection::topRightVertex:
			topQuad.translateTopRight(delta);
			break;
		case Selection::middleLeftVertex:
			topQuad.translateBottomLeft(delta);
			bottomQuad.translateTopLeft(delta);
			break;
		case Selection::middleRightVertex:
			topQuad.translateBottomRight(delta);
			bottomQuad.translateTopRight(delta);
			break;
		case Selection::bottomLeftVertex:
			bottomQuad.translateBottomLeft(delta);
			break;
		case Selection::bottomRightVertex:
			bottomQuad.translateBottomRight(delta);
			break;
		case Selection::topEdge:
			topQuad.translateTopLeft(delta);
			topQuad.translateTopRight(delta);
			break;
		case Selection::topLeftEdge:
			topQuad.translateTopLeft(delta);
			topQuad.translateBottomLeft(delta);
			bottomQuad.translateTopLeft(delta);
			break;
		case Selection::bottomLeftEdge:
			topQuad.translateBottomLeft(delta);
			bottomQuad.translateTopLeft(delta);
			bottomQuad.translateBottomLeft(delta);
			break;
		case Selection::topRightEdge:
			topQuad.translateTopRight(delta);
			topQuad.translateBottomRight(delta);
			bottomQuad.translateTopRight(delta);
			break;
		case Selection::middleEdge:
			topQuad.translateBottomLeft(delta);
			topQuad.translateBottomRight(delta);
			bottomQuad.translateTopLeft(delta);
			bottomQuad.translateTopRight(delta);
			break;
		case Selection::bottomRightEdge:
			topQuad.translateBottomRight(delta);
			bottomQuad.translateTopRight(delta);
			bottomQuad.translateBottomRight(delta);
			break;
		case Selection::bottomEdge:
			bottomQuad.translateBottomLeft(delta);
			bottomQuad.translateBottomRight(delta);
			break;
		default:
			break;
	}
}

void TreeQuad::draw()
{
	topQuad.calculateHomography();
	ofPushMatrix();
		ofMultMatrix(topQuad.getMatrix());
		source->bind();
		topQuad.getMesh().draw();
		source->unbind();
	ofPopMatrix();

	bottomQuad.calculateHomography();
	ofPushMatrix();
		ofMultMatrix(bottomQuad.getMatrix());
		source->bind();
		bottomQuad.getMesh().draw();
		source->unbind();
	ofPopMatrix();

	if (inputEnabled) {
		ofPushStyle();
		ofNoFill();
			ofSetColor(255);
			ofSetLineWidth(2);
			ofCircle(topQuad.getTopLeft(), selectionDistance);
			ofCircle(topQuad.getTopRight(), selectionDistance);
			ofCircle(topQuad.getBottomLeft(), selectionDistance);
			ofCircle(topQuad.getBottomRight(), selectionDistance);
			ofCircle(bottomQuad.getBottomLeft(), selectionDistance);
			ofCircle(bottomQuad.getBottomRight(), selectionDistance);
			ofCircle(topQuad.getTopMidpoint(), selectionDistance);
			ofCircle(topQuad.getLeftMidpoint(), selectionDistance);
			ofCircle(topQuad.getRightMidpoint(), selectionDistance);
			ofCircle(topQuad.getBottomMidpoint(), selectionDistance);
			ofCircle(bottomQuad.getLeftMidpoint(), selectionDistance);
			ofCircle(bottomQuad.getRightMidpoint(), selectionDistance);
			ofCircle(bottomQuad.getBottomMidpoint(), selectionDistance);
		ofPopStyle();
	}
}

ofXml TreeQuad::saveToXml(string name) {
	ofXml xml;

	xml.addChild(name);
	xml.setTo(name);

	xml.addChild("source");
	xml.setTo("source");
	
	string path = source->getPath();
	string relativeImagePath = ofFilePath::isAbsolute(path) ? ofFilePath::makeRelative(ofToDataPath("./", true), path) : path;
	xml.addValue("path", relativeImagePath);

	SourceType type = source->getType();
	if (type == SourceType::image) xml.addValue("type", "image");
	else if (type == SourceType::video) xml.addValue("type", "video");

	xml.setToParent();

	xml.addValue("animationDuration", animationDurationSeconds);

	ofXml topQuadXml = topQuad.saveToXml("topQuad");
	ofXml bottomQuadXml = topQuad.saveToXml("bottomQuad");
	ofXml startTopQuadXml = topQuad.saveToXml("startTopQuad");
	ofXml endTopQuadXml = topQuad.saveToXml("endTopQuad");
	ofXml startBottomQuadXml = topQuad.saveToXml("startBottomQuad");
	ofXml endBottomQuadXml = topQuad.saveToXml("endBottomQuad");
	xml.addXml(topQuadXml);
	xml.addXml(bottomQuadXml);
	xml.addXml(startTopQuadXml);
	xml.addXml(endTopQuadXml);
	xml.addXml(startBottomQuadXml);
	xml.addXml(endBottomQuadXml);
	
	return xml;
}

void TreeQuad::loadFromXml(ofXml& xml) {
	string type = xml.getValue("source/type");
	string path = xml.getValue("source/path");
	if (type == "image") source = new ImageSource(path);
	else if (type == "video") source = new VideoSource(path);

	animationDurationSeconds = xml.getFloatValue("animationDuration");

	topQuad.setVertices(
		ofVec3f(xml.getFloatValue("topQuad/topLeft/x"), xml.getFloatValue("topQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("topQuad/topRight/x"), xml.getFloatValue("topQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("topQuad/bottomRight/x"), xml.getFloatValue("topQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("topQuad/bottomLeft/x"), xml.getFloatValue("topQuad/bottomLeft/y"), 0)
	);
	topQuad.setTexCoords(
		ofVec3f(xml.getFloatValue("topQuad/topLeft/u"), xml.getFloatValue("topQuad/topLeft/v"), 0),
		ofVec3f(xml.getFloatValue("topQuad/topRight/u"), xml.getFloatValue("topQuad/topRight/v"), 0),
		ofVec3f(xml.getFloatValue("topQuad/bottomRight/u"), xml.getFloatValue("topQuad/bottomRight/v"), 0),
		ofVec3f(xml.getFloatValue("topQuad/bottomLeft/u"), xml.getFloatValue("topQuad/bottomLeft/v"), 0)
	);
	bottomQuad.setVertices(
		ofVec3f(xml.getFloatValue("bottomQuad/topLeft/x"), xml.getFloatValue("bottomQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/topRight/x"), xml.getFloatValue("bottomQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/bottomRight/x"), xml.getFloatValue("bottomQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/bottomLeft/x"), xml.getFloatValue("bottomQuad/bottomLeft/y"), 0)
	);
	bottomQuad.setTexCoords(
		ofVec3f(xml.getFloatValue("bottomQuad/topLeft/u"), xml.getFloatValue("bottomQuad/topLeft/v"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/topRight/u"), xml.getFloatValue("bottomQuad/topRight/v"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/bottomRight/u"), xml.getFloatValue("bottomQuad/bottomRight/v"), 0),
		ofVec3f(xml.getFloatValue("bottomQuad/bottomLeft/u"), xml.getFloatValue("bottomQuad/bottomLeft/v"), 0)
	);


	startTopQuad.setVertices(
		ofVec3f(xml.getFloatValue("startTopQuad/topLeft/x"), xml.getFloatValue("startTopQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("startTopQuad/topRight/x"), xml.getFloatValue("startTopQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("startTopQuad/bottomRight/x"), xml.getFloatValue("startTopQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("startTopQuad/bottomLeft/x"), xml.getFloatValue("startTopQuad/bottomLeft/y"), 0)
	);
	endTopQuad.setVertices(
		ofVec3f(xml.getFloatValue("endTopQuad/topLeft/x"), xml.getFloatValue("endTopQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("endTopQuad/topRight/x"), xml.getFloatValue("endTopQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("endTopQuad/bottomRight/x"), xml.getFloatValue("endTopQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("endTopQuad/bottomLeft/x"), xml.getFloatValue("endTopQuad/bottomLeft/y"), 0)
	);
	startBottomQuad.setVertices(
		ofVec3f(xml.getFloatValue("startBottomQuad/topLeft/x"), xml.getFloatValue("startBottomQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("startBottomQuad/topRight/x"), xml.getFloatValue("startBottomQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("startBottomQuad/bottomRight/x"), xml.getFloatValue("startBottomQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("startBottomQuad/bottomLeft/x"), xml.getFloatValue("startBottomQuad/bottomLeft/y"), 0)
	);
	endBottomQuad.setVertices(
		ofVec3f(xml.getFloatValue("endBottomQuad/topLeft/x"), xml.getFloatValue("endBottomQuad/topLeft/y"), 0),
		ofVec3f(xml.getFloatValue("endBottomQuad/topRight/x"), xml.getFloatValue("endBottomQuad/topRight/y"), 0),
		ofVec3f(xml.getFloatValue("endBottomQuad/bottomRight/x"), xml.getFloatValue("endBottomQuad/bottomRight/y"), 0),
		ofVec3f(xml.getFloatValue("endBottomQuad/bottomLeft/x"), xml.getFloatValue("endBottomQuad/bottomLeft/y"), 0)
	);
}

bool TreeQuad::isPointInside(ofVec2f pos)
{
	return (topQuad.isPointInside(pos) || bottomQuad.isPointInside(pos));
}

bool TreeQuad::isInputEnabled()
{
	return inputEnabled;
}

void TreeQuad::setAnimationStartShape()
{
	startTopQuad = topQuad;
	startBottomQuad = bottomQuad;
}

void TreeQuad::setAnimationEndShape()
{
	endTopQuad = topQuad;
	endBottomQuad = bottomQuad;
}

void TreeQuad::updateAnimation(ofEventArgs& args)
{
	animationProgress.update(ofGetLastFrameTime());
	float t = animationProgress.val();
	setShapeFromAnimation(t);
}

void TreeQuad::setShapeFromAnimation(float animationFraction)
{
	float t = animationFraction;
	topQuad.setTopLeft(startTopQuad.getTopLeft() * (1 - t) + endTopQuad.getTopLeft() * t);
	topQuad.setTopRight(startTopQuad.getTopRight() * (1 - t) + endTopQuad.getTopRight() * t);
	topQuad.setBottomLeft(startTopQuad.getBottomLeft() * (1 - t) + endTopQuad.getBottomLeft() * t);
	topQuad.setBottomRight(startTopQuad.getBottomRight() * (1 - t) + endTopQuad.getBottomRight() * t);
	bottomQuad.setTopLeft(startBottomQuad.getTopLeft() * (1 - t) + endBottomQuad.getTopLeft() * t);
	bottomQuad.setTopRight(startBottomQuad.getTopRight() * (1 - t) + endBottomQuad.getTopRight() * t);
	bottomQuad.setBottomLeft(startBottomQuad.getBottomLeft() * (1 - t) + endBottomQuad.getBottomLeft() * t);
	bottomQuad.setBottomRight(startBottomQuad.getBottomRight() * (1 - t) + endBottomQuad.getBottomRight() * t);
}

void TreeQuad::playAnimation()
{
	if (!isAnimating) {
		ofAddListener(ofEvents().update, this, &TreeQuad::updateAnimation);
	}
	isAnimating = true;
	animationProgress.setCurve(LINEAR);
	animationProgress.setRepeatType(LOOP);
	animationProgress.setDuration(animationDurationSeconds);
	animationProgress.animateFromTo(0, 1);
}

void TreeQuad::stopAnimation()
{
	if (isAnimating) {
		isAnimating = false;
		ofRemoveListener(ofEvents().update, this, &TreeQuad::updateAnimation);
		setShapeFromAnimation(0);
	}
}

void TreeQuad::setSource(BaseSource * newSource)
{
	if (source != nullptr) {
		delete source;
	}
	this->source = newSource;
}

void TreeQuad::setAnimationDuration(float seconds)
{
	animationDurationSeconds = seconds;
}

float TreeQuad::getAnimationDuration()
{
	return animationDurationSeconds;
}

void TreeQuad::setTextureSplit(float fraction)
{
	ofRectangle r = topQuad.getMeshBoundingBox();
	float w = source->getWidth();
	float h = source->getHeight();
	topQuad.setTexCoordsFromRect(ofRectangle(0, 0, 1, fraction));
	topQuad.setVetricesFromRect(ofRectangle(r.x, r.y, w, fraction * h));
	bottomQuad.setTexCoordsFromRect(ofRectangle(0, fraction, 1, 1 - fraction));
	bottomQuad.setVetricesFromRect(ofRectangle(r.x, r.y + fraction * h, w, (1 - fraction) * h));
}

BaseSource * TreeQuad::getSource()
{
	return source;
}
