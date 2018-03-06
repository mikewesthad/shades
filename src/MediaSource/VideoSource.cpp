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
	video.getTexture().bind();
	//video.bind();
}

void VideoSource::unbind()
{
	video.getTexture().unbind();
	//video.unbind();
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
	#ifdef TARGET_RASPBERRY_PI
		video.setSpeed(speed);
	#else
		video.setSpeed(speed, false);
	#endif
}

void VideoSource::update(ofEventArgs& args)
{
	video.update();
}
