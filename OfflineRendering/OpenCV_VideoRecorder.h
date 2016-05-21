#pragma once
#include "opencv\cv.h"
#include "opencv\highgui.h"

class OpenCV_VideoRecorder {
	CvVideoWriter * writer;
public:
	void init();
	void beginRendering();
	void endRendering();
};