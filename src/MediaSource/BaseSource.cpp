#include "BaseSource.h"



BaseSource::BaseSource()
{
}

BaseSource::~BaseSource()
{
}

string BaseSource::getPath()
{
	return path;
}

SourceType BaseSource::getType()
{
	return sourceType;
}