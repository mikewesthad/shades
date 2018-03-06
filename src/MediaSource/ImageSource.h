#pragma once

#include "BaseSource.h"
#include "ofMain.h"

class ImageSource: public BaseSource
{
public:
	ImageSource(string imagePath);
	~ImageSource();

	void loadImage(string imagePath);
	void bind();
	void unbind();
	int getWidth();
	int getHeight();

private:
	ofImage image;
};

