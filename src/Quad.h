#pragma once

#include "ofMain.h"


class Quad
{
	enum class CornerSelected { topLeft, topRight, bottomLeft, bottomRight, none };

	public:
		Quad();
		~Quad();

		void onMousePressed(ofMouseEventArgs & mouseArgs);
		void onMouseMoved(ofMouseEventArgs & mouseArgs);
		void onMouseDragged(ofMouseEventArgs & mouseArgs);
		void onMouseReleased(ofMouseEventArgs & mouseArgs);
		void UpdateSelectedCorner(ofVec2f newPosition);
		void calculateHomography();
		ofRectangle getMeshBoundingBox();
		ofXml saveToXml(string name = "quad");
		void setFromRect(ofRectangle rect);
		void setTexCoordsFromRect(ofRectangle rect);
		void setVetricesFromRect(ofRectangle rect);
		void setTexCoords(ofVec2f topLeft, ofVec2f topRight, ofVec2f bottomRight, ofVec2f bottomLeft);
		void setVertices(ofVec3f topLeft, ofVec3f topRight, ofVec3f bottomRight, ofVec3f bottomLeft);
		ofVec3f getVertex(int i);
		ofVec3f getTopLeft();
		ofVec3f getTopRight();
		ofVec3f getBottomRight();
		ofVec3f getBottomLeft();
		ofVec3f getTopMidpoint();
		ofVec3f getLeftMidpoint();
		ofVec3f getRightMidpoint();
		ofVec3f getBottomMidpoint();
		void setTopLeft(ofVec3f pos);
		void setTopRight(ofVec3f pos);
		void setBottomRight(ofVec3f pos);
		void setBottomLeft(ofVec3f pos);
		bool isPointInside(ofVec2f pos);
		void translate(ofVec3f delta);
		void translateTopLeft(ofVec3f delta);
		void translateTopRight(ofVec3f delta);
		void translateBottomRight(ofVec3f delta);
		void translateBottomLeft(ofVec3f delta);

		float* getMatrix();
		ofMesh getMesh();

	private:
		float matrix[16];
		ofMesh mesh;

		CornerSelected selected = CornerSelected::none;
		float selectionDistance = 50;

		const static int TOP_LEFT = 0;
		const static int TOP_RIGHT = 1;
		const static int BOTTOM_RIGHT = 2;
		const static int BOTTOM_LEFT = 3;
};

