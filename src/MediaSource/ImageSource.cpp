#include "ImageSource.h"

ImageSource::ImageSource(string imagePath)
{
	sourceType = SourceType::image;
	loadImage(imagePath);
}

ImageSource::~ImageSource()
{
}

void ImageSource::loadImage(string imagePath) {
	path = imagePath;
	image.load(imagePath);
}

void ImageSource::bind()
{
	image.bind();
}

void ImageSource::unbind()
{
	image.unbind();
}

int ImageSource::getWidth()
{
	return image.getWidth();
}

int ImageSource::getHeight()
{
	return image.getHeight();
}
