#pragma once
#include "opencv\cv.h"
#include "opencv\highgui.h"

class OpenCV_VideoRecorder {
public:
	void init();
	void beginRendering();
	void endRendering();
};