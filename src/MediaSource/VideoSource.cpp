#include "VideoSource.h"



VideoSource::~VideoSource()
{
	ofRemoveListener(ofEvents().update, this, &VideoSource::update);
}

VideoSource::VideoSource(string videoPath)
{
	sourceType = SourceType::video;
	loadVideo(videoPath);
}

void VideoSource::loadVideo(string videoPath)
{
	path = videoPath;

	video.load(videoPath);
	video.setLoopState(OF_LOOP_NORMAL);
	video.play();
	video.setVolume(0);
	ofAddListener(ofEvents().update, this, &VideoSource::update);
}

void VideoSource::bind()
{
	#ifndef TARGET_OSX
		video.getTexture().bind();
	#else
		video.bind();
	#endif
}

void VideoSource::unbind()
{
	#ifndef TARGET_OSX
		video.getTexture().unbind();
	#else
		video.unbind();
	#endif
}

int VideoSource::getWidth()
{
	return video.getWidth();
}

int VideoSource::getHeight()
{
	return video.getHeight();
}

void VideoSource::setSpeed(float speed)
{
	#ifndef TARGET_OSX
		video.setSpeed(speed, false);
	#else
		video.setSpeed(speed);
	#endif
}

void VideoSource::update(ofEventArgs& args)
{
	video.update();
}
