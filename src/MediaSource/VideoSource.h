#pragma once

#include "BaseSource.h"
#include "ofMain.h"

#ifdef TARGET_RASPBERRY_PI
	
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
		ofVideoPlayer video;
	#else
		ofxWMFVideoPlayer video;
	#endif
};

