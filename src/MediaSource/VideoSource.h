#pragma once

#include "BaseSource.h"
#include "ofMain.h"

#ifndef TARGET_OSX
	#include "ofxWMFVideoPlayer.h"
#endif

class VideoSource : public BaseSource
{
public:
	~VideoSource();
	VideoSource(string videoPath);

	void loadVideo(string videoPath);
	void bind();
	void unbind();
	int getWidth();
	int getHeight();
	void setSpeed(float speed);

private:
	void update(ofEventArgs& args);

	#ifndef TARGET_OSX
		ofxWMFVideoPlayer video;
	#else
		ofVideoPlayer video;
	#endif
};

