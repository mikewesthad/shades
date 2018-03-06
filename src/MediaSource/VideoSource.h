#pragma once

#include "BaseSource.h"
#include "ofMain.h"

#ifdef TARGET_RASPBERRY_PI
	#include "ofxOMXPlayer.h"
#else
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

	#ifdef TARGET_RASPBERRY_PI
		ofxOMXPlayer video;
	#elif TARGET_OSX
		ofVideoPlayer video;
	#else
		ofxWMFVideoPlayer video;
	#endif
};

