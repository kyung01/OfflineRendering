#include "OpenCV_VideoRecorder.h"
#include "GLFW_GLEW.h"
#include "GlobalVariables.h"
#include <iostream>
#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
void OpenCV_VideoRecorder::init()
{
	float fps = 1;
	writer = cvCreateVideoWriter("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, 
		CvSize(GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT), true);
	if (!writer)
	{
		std::cout << "OpenCV_VideoRecorder Initialization failed" << std::endl;
		system("pause");
	}

	/*
	IplImage* img1 = cvLoadImage("img1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	IplImage* img2 = cvLoadImage("img2.jpg", CV_LOAD_IMAGE_UNCHANGED);

	float fps = 20;
	CvVideoWriter* writer = cvCreateVideoWriter("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, cvGetSize(img1), true);
	if (!writer)
	{
	fprintf(stderr, "VideoWriter failed!\n");
	return -1;
	}

	cvWriteFrame(writer, img1);
	cvWriteFrame(writer, img2);

	cvReleaseVideoWriter(&writer);
	cvReleaseImage(&img1);
	cvReleaseImage(&img2);
	*/
}

void OpenCV_VideoRecorder::beginRendering()
{
	
}

void OpenCV_VideoRecorder::endRendering()
{
	//cv::Mat img;
	//cv::video
	cv::VideoWriter writerNew;
	cv::Mat img(GlobalVariables::CONTEXT_HEIGHT,GlobalVariables::CONTEXT_WIDTH, CV_8U);
	writerNew << img;
	//(*writer).get(1);
	//glReadPixels(0, 0,img.cols,img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
	
	
}
