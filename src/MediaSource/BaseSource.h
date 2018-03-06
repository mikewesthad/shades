#pragma once

#include "ofMain.h"

enum class SourceType {
	none,
	image,
	video
};

class BaseSource
{
public:
	BaseSource();
	virtual ~BaseSource();
	string getPath();
	SourceType getType();
	virtual void bind() = 0;
	virtual void unbind() = 0;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;

protected:
	string path;
	SourceType sourceType = SourceType::none;
};

