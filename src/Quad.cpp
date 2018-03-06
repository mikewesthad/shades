#include "Quad.h"
#include "./Utils/HomographyHelper.h"

Quad::Quad()
{
	//ofAddListener(ofEvents().mouseMoved, this, &Quad::onMouseMoved);
	//ofAddListener(ofEvents().mousePressed, this, &Quad::onMousePressed);
	//ofAddListener(ofEvents().mouseReleased, this, &Quad::onMouseReleased);
	//ofAddListener(ofEvents().mouseDragged, this, &Quad::onMouseDragged);

	mesh.clear();

	// Clockwise - top left, top right, bottom right, bottom left
	mesh.addVertex(ofVec3f(0, 0));
	mesh.addVertex(ofVec3f(800, 0));
	mesh.addVertex(ofVec3f(800, 600));
	mesh.addVertex(ofVec3f(0, 600));
	
	mesh.addTriangle(0, 1, 2);
	mesh.addTriangle(2, 3, 0);

	mesh.addTexCoord(ofVec3f(0, 0));
	mesh.addTexCoord(ofVec3f(1, 0));
	mesh.addTexCoord(ofVec3f(1, 1));
	mesh.addTexCoord(ofVec3f(0, 1));
}

Quad::~Quad()
{
	//ofRemoveListener(ofEvents().mouseMoved, this, &Quad::onMouseMoved);
	//ofRemoveListener(ofEvents().mousePressed, this, &Quad::onMousePressed);
	//ofRemoveListener(ofEvents().mouseReleased, this, &Quad::onMouseReleased);
	//ofRemoveListener(ofEvents().mouseDragged, this, &Quad::onMouseDragged);
}

void Quad::setFromRect(ofRectangle rect)
{
	mesh.setVertex(TOP_LEFT, ofVec3f(rect.getLeft(), rect.getTop()));
	mesh.setVertex(TOP_RIGHT, ofVec3f(rect.getRight(), rect.getTop()));
	mesh.setVertex(BOTTOM_RIGHT, ofVec3f(rect.getRight(), rect.getBottom()));
	mesh.setVertex(BOTTOM_LEFT, ofVec3f(rect.getLeft(), rect.getBottom()));

	mesh.setTexCoord(TOP_LEFT, ofVec2f(0, 0));
	mesh.setTexCoord(TOP_RIGHT, ofVec2f(1, 0));
	mesh.setTexCoord(BOTTOM_RIGHT, ofVec2f(1, 1));
	mesh.setTexCoord(BOTTOM_LEFT, ofVec2f(0, 1));
}

void Quad::setTexCoordsFromRect(ofRectangle rect)
{
	mesh.setTexCoord(TOP_LEFT, ofVec2f(rect.getLeft(), rect.getTop()));
	mesh.setTexCoord(TOP_RIGHT, ofVec2f(rect.getRight(), rect.getTop()));
	mesh.setTexCoord(BOTTOM_RIGHT, ofVec2f(rect.getRight(), rect.getBottom()));
	mesh.setTexCoord(BOTTOM_LEFT, ofVec2f(rect.getLeft(), rect.getBottom()));
}

void Quad::setVetricesFromRect(ofRectangle rect)
{
	mesh.setVertex(TOP_LEFT, ofVec3f(rect.getLeft(), rect.getTop()));
	mesh.setVertex(TOP_RIGHT, ofVec3f(rect.getRight(), rect.getTop()));
	mesh.setVertex(BOTTOM_RIGHT, ofVec3f(rect.getRight(), rect.getBottom()));
	mesh.setVertex(BOTTOM_LEFT, ofVec3f(rect.getLeft(), rect.getBottom()));
}

void Quad::onMousePressed(ofMouseEventArgs& mouseArgs) {
	if (mouseArgs.button != 0) return;

	selected = CornerSelected::none;

	float d = mouseArgs.distance(this->mesh.getVertex(TOP_LEFT));
	if (d <= this->selectionDistance) this->selected = CornerSelected::topLeft;

	d = mouseArgs.distance(this->mesh.getVertex(TOP_RIGHT));
	if (d <= this->selectionDistance) this->selected = CornerSelected::topRight;

	d = mouseArgs.distance(this->mesh.getVertex(BOTTOM_LEFT));
	if (d <= this->selectionDistance) this->selected = CornerSelected::bottomLeft;

	d = mouseArgs.distance(this->mesh.getVertex(BOTTOM_RIGHT));
	if (d <= this->selectionDistance) this->selected = CornerSelected::bottomRight;

	// TODO: selected closest
	UpdateSelectedCorner(mouseArgs);
}

void Quad::onMouseMoved(ofMouseEventArgs& mouseArgs) {
	UpdateSelectedCorner(mouseArgs);
}

void Quad::onMouseDragged(ofMouseEventArgs& mouseArgs) {
	if (mouseArgs.button != 0) return;
	UpdateSelectedCorner(mouseArgs);
}

void Quad::onMouseReleased(ofMouseEventArgs& mouseArgs) {
	if (mouseArgs.button != 0) return;
	selected = CornerSelected::none;
}

void Quad::UpdateSelectedCorner(ofVec2f newPosition) {
	switch (this->selected)
	{
		case CornerSelected::topLeft: 
			mesh.setVertex(TOP_LEFT, newPosition);
			break;
		case CornerSelected::topRight:
			mesh.setVertex(TOP_RIGHT, newPosition);
			break;
		case CornerSelected::bottomLeft:
			mesh.setVertex(BOTTOM_LEFT, newPosition);
			break;
		case CornerSelected::bottomRight:
			mesh.setVertex(BOTTOM_RIGHT, newPosition);
			break;
		default:
			break;
	}
}

float* Quad::getMatrix()
{
	return this->matrix;
}

ofMesh Quad::getMesh()
{
	ofMesh m = mesh;
	ofRectangle box = getMeshBoundingBox();
	m.setVertex(0, ofVec3f(0, 0, 0));
	m.setVertex(1, ofVec3f(box.width, 0, 0));
	m.setVertex(2, ofVec3f(box.width, box.height, 0));
	m.setVertex(3, ofVec3f(0, box.height, 0));

	return m;
}

void Quad::calculateHomography()
{
	float src[4][2];
	float dst[4][2];

	ofRectangle box = getMeshBoundingBox();
	src[0][0] = 0;
	src[0][1] = 0;
	src[1][0] = box.width;
	src[1][1] = 0;
	src[2][0] = box.width;
	src[2][1] = box.height;
	src[3][0] = 0;
	src[3][1] = box.height;

	dst[0][0] = this->mesh.getVertex(0).x;
	dst[0][1] = this->mesh.getVertex(0).y;
	dst[1][0] = this->mesh.getVertex(1).x;
	dst[1][1] = this->mesh.getVertex(1).y;
	dst[2][0] = this->mesh.getVertex(2).x;
	dst[2][1] = this->mesh.getVertex(2).y;
	dst[3][0] = this->mesh.getVertex(3).x;
	dst[3][1] = this->mesh.getVertex(3).y;

	HomographyHelper::findHomography(src, dst, this->matrix);
}

ofRectangle Quad::getMeshBoundingBox() {
	float minX = 10000.0f;
	float minY = 10000.0f;
	float maxX = 0.0f;
	float maxY = 0.0f;

	for (int i = 0; i < mesh.getVertices().size(); ++i) {
		if (mesh.getVertices()[i].x < minX) {
			minX = mesh.getVertices()[i].x;
		}

		if (mesh.getVertices()[i].y < minY) {
			minY = mesh.getVertices()[i].y;
		}

		if (mesh.getVertices()[i].x > maxX) {
			maxX = mesh.getVertices()[i].x;
		}

		if (mesh.getVertices()[i].y > maxY) {
			maxY = mesh.getVertices()[i].y;
		}
	}

	ofRectangle boundingBox = ofRectangle(ofPoint(minX, minY), ofPoint(maxX, maxY));
	return boundingBox;
}

ofXml Quad::saveToXml(string name) {
	ofXml xml;

	xml.addChild(name);
	xml.setTo(name);

	xml.addChild("topLeft");
	xml.setTo("topLeft");
	xml.addValue("x", mesh.getVertex(TOP_LEFT).x);
	xml.addValue("y", mesh.getVertex(TOP_LEFT).y);
	xml.addValue("u", mesh.getTexCoord(TOP_LEFT).x);
	xml.addValue("v", mesh.getTexCoord(TOP_LEFT).y);
	xml.setTo("../");

	xml.addChild("topRight");
	xml.setTo("topRight");
	xml.addValue("x", mesh.getVertex(TOP_RIGHT).x);
	xml.addValue("y", mesh.getVertex(TOP_RIGHT).y);
	xml.addValue("u", mesh.getTexCoord(TOP_RIGHT).x);
	xml.addValue("v", mesh.getTexCoord(TOP_RIGHT).y);
	xml.setTo("../");

	xml.addChild("bottomRight");
	xml.setTo("bottomRight");
	xml.addValue("x", mesh.getVertex(BOTTOM_RIGHT).x);
	xml.addValue("y", mesh.getVertex(BOTTOM_RIGHT).y);
	xml.addValue("u", mesh.getTexCoord(BOTTOM_RIGHT).x);
	xml.addValue("v", mesh.getTexCoord(BOTTOM_RIGHT).y);
	xml.setTo("../");

	xml.addChild("bottomLeft");
	xml.setTo("bottomLeft");
	xml.addValue("x", mesh.getVertex(BOTTOM_LEFT).x);
	xml.addValue("y", mesh.getVertex(BOTTOM_LEFT).y);
	xml.addValue("u", mesh.getTexCoord(BOTTOM_LEFT).x);
	xml.addValue("v", mesh.getTexCoord(BOTTOM_LEFT).y);

	return xml;
}

void Quad::setTexCoords(ofVec2f topLeft, ofVec2f topRight, ofVec2f bottomRight, ofVec2f bottomLeft)
{ 
	mesh.setTexCoord(TOP_LEFT, topLeft);
	mesh.setTexCoord(TOP_RIGHT, topRight);
	mesh.setTexCoord(BOTTOM_RIGHT, bottomRight);
	mesh.setTexCoord(BOTTOM_LEFT, bottomLeft);

}

void Quad::setVertices(ofVec3f topLeft, ofVec3f topRight, ofVec3f bottomRight, ofVec3f bottomLeft)
{
	mesh.setVertex(TOP_LEFT, topLeft);
	mesh.setVertex(TOP_RIGHT, topRight);
	mesh.setVertex(BOTTOM_RIGHT, bottomRight);
	mesh.setVertex(BOTTOM_LEFT, bottomLeft);
}

ofVec3f Quad::getVertex(int i)
{
	if (i >= 4) throw std::invalid_argument("Index out of range");
	return mesh.getVertex(i);
}

ofVec3f Quad::getTopLeft()
{
	return mesh.getVertex(TOP_LEFT);
}

ofVec3f Quad::getTopRight()
{
	return mesh.getVertex(TOP_RIGHT);
}

ofVec3f Quad::getBottomLeft()
{
	return mesh.getVertex(BOTTOM_LEFT);
}

ofVec3f Quad::getTopMidpoint()
{
	return (getTopLeft() + getTopRight()) / 2;
}

ofVec3f Quad::getLeftMidpoint()
{
	return (getTopLeft() + getBottomLeft()) / 2;
}

ofVec3f Quad::getRightMidpoint()
{
	return (getTopRight() + getBottomRight()) / 2;
}

ofVec3f Quad::getBottomMidpoint()
{
	return (getBottomLeft() + getBottomRight()) / 2;
}

void Quad::setTopLeft(ofVec3f pos)
{
	mesh.setVertex(TOP_LEFT, pos);
}

void Quad::setTopRight(ofVec3f pos)
{
	mesh.setVertex(TOP_RIGHT, pos);
}

void Quad::setBottomRight(ofVec3f pos)
{
	mesh.setVertex(BOTTOM_RIGHT, pos);
}

void Quad::setBottomLeft(ofVec3f pos)
{
	mesh.setVertex(BOTTOM_LEFT, pos);
}

ofVec3f Quad::getBottomRight()
{
	return mesh.getVertex(BOTTOM_RIGHT);
}

bool Quad::isPointInside(ofVec2f pos)
{
	return ofInsidePoly(pos, mesh.getVertices());
}

void Quad::translate(ofVec3f delta)
{
	setTopLeft(getTopLeft() + delta);
	setTopRight(getTopRight() + delta);
	setBottomRight(getBottomRight() + delta);
	setBottomLeft(getBottomLeft() + delta);
}

void Quad::translateTopLeft(ofVec3f delta)
{
	setTopLeft(getTopLeft() + delta);
}

void Quad::translateTopRight(ofVec3f delta)
{
	setTopRight(getTopRight() + delta);
}

void Quad::translateBottomRight(ofVec3f delta)
{
	setBottomRight(getBottomRight() + delta);
}

void Quad::translateBottomLeft(ofVec3f delta)
{
	setBottomLeft(getBottomLeft() + delta);
}
