#include "VideoSource.h"



VideoSource::~VideoSource()
{
	#ifdef TARGET_RASPBERRY_PI
		// noop
	#else
		ofRemoveListener(ofEvents().update, this, &VideoSource::update);
	#endif
}

VideoSource::VideoSource(string videoPath)
{
	#ifdef TARGET_RASPBERRY_PI
		ofxOMXPlayerSettings settings;
		settings.videoPath = videoPath;
		settings.useHDMIForAudio = true;
		settings.enableTexture = true;
		settings.enableLooping = true;
		settings.enableAudio = false;
		settings.doFlipTexture = true;
		video.setup(settings);
	#endif

	sourceType = SourceType::video;
	loadVideo(videoPath);
}

void VideoSource::loadVideo(string videoPath)
{
	path = videoPath;

	#ifdef TARGET_RASPBERRY_PI
		video.loadMovie(videoPath);
	#else
		video.load(videoPath);
		video.setLoopState(OF_LOOP_NORMAL);
		video.play();
		video.setVolume(0);
		ofAddListener(ofEvents().update, this, &VideoSource::update);
	#endif
}

void VideoSource::bind()
{
	#ifdef TARGET_RASPBERRY_PI
		video.getTextureReference().bind();
	#else 
		video.getTexture().bind();
	#endif
	//video.bind();
}

void VideoSource::unbind()
{
	#ifdef TARGET_RASPBERRY_PI
		video.getTextureReference().unbind();
	#else 
		video.getTexture().unbind();
	#endif
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
		// noop
	#else
		video.setSpeed(speed, false);
	#endif
}

void VideoSource::update(ofEventArgs& args)
{
	#ifdef TARGET_RASPBERRY_PI
		// noop
	#else
		video.update();
	#endif
}
