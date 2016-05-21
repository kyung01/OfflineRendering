#pragma once
#include "opencv\cv.h"
#include "opencv\highgui.h"
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"

class OpenCV_VideoRecorder {
	//CvVideoWriter * writer;
	cv::VideoWriter writer;
public:
	void init();
	void beginRendering();
	void endRendering();
	void end();
};