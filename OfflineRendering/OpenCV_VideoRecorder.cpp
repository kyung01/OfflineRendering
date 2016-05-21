#include "OpenCV_VideoRecorder.h"
#include "GLFW_GLEW.h"
#include "GlobalVariables.h"
#include <iostream>
void OpenCV_VideoRecorder::init()
{
	float fps = 1;
	/*
	writer = cvCreateVideoWriter("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, 
		CvSize(GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT), true);
	if (!writer)
	{
		std::cout << "OpenCV_VideoRecorder Initialization failed" << std::endl;
		system("pause");
	}
	*/

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
	//return;
	//std::cout << "OpenCV_VideoRecorder RENDERING" << std::endl;
	float fps = 20;
	if (!writer.isOpened()) {
		std::cout << "OpenCV_VideoRecorder OPENED WRTIER " << std::endl;
		GLint dims[4] = { 0 };
		glGetIntegerv(GL_VIEWPORT, dims);
		GLint fbWidth = dims[2];
		GLint fbHeight = dims[3];

		writer.open(
			"Out.avi",
			//RGB VGPX
			//VDTZ
			//IPDV
			//DMK2		DIV5 CGDI ASVX  <- AFLI AFLC(cannotfind) AEMI
			CV_FOURCC('M', 'J', 'P', 'G'),
			fps,
			cv::Size(fbWidth, fbHeight),
			true);
	}
	
}

void OpenCV_VideoRecorder::endRendering()
{
	//return;
	//std::cout << "R";
	//cv::Mat img;
	//cv::video
	//cv::Mat frame(GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT, CV_8UC3);
	cv::Mat frame(GlobalVariables::CONTEXT_HEIGHT, GlobalVariables::CONTEXT_WIDTH, CV_8UC3);

	glReadPixels(0, 0,frame.cols, frame.rows, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
	cv::flip(frame, frame, 0);

	writer.write(frame);
	//writer << img;
	//(*writer).get(1);
	
	
}

void OpenCV_VideoRecorder::end()
{
	return;
	float fps = 2;
	
	{
	std::cout << "WRITING" << std::endl;
	IplImage* img = cvLoadImage("img1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	cv::Mat frame = cv::cvarrToMat(img);
	CvSize imgSize = cvGetSize(img);
	cv::VideoWriter writerNew("out.avi",cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, imgSize, true);
	if (!writerNew.isOpened())
	{
	std::cout << "FAIL";
	}
	cv::Mat blankFrame(imgSize, CV_8UC3);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);
	writerNew.write(blankFrame);

	}
	return;

	/*
	{
		IplImage* img1 = cvLoadImage("img1.jpg", CV_LOAD_IMAGE_UNCHANGED);
		//CvVideoWriter* writerNew = cvCreateVideoWriter("Out02.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps,
		//	cv::Size(GlobalVariables::CONTEXT_WIDTH, GlobalVariables::CONTEXT_HEIGHT), true);

		CvVideoWriter* writerNew = cvCreateVideoWriter("Out02.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps,
			cvGetSize(img1), true);
		cvWriteFrame(writerNew, img1);
		cvReleaseImage(&img1);
		cvReleaseVideoWriter(&writerNew);
	}
	return;
	*/
	if (writer.isOpened()) {
		std::cout << "OpenCV_VideoRecorder CLOSING WRTIER " << std::endl;
		writer.release();
	}

	return;

	{
		
		IplImage* img1 = cvLoadImage("img1.jpg", CV_LOAD_IMAGE_UNCHANGED);
		IplImage* img2 = cvLoadImage("img2.jpg", CV_LOAD_IMAGE_UNCHANGED);

		std::cout << cvGetSize(img1).width<< " " << cvGetSize(img1).height << std::endl;
		

		CvVideoWriter* writer = cvCreateVideoWriter("out.avi", CV_FOURCC('M', 'J', 'P', 'G'), fps, cvGetSize(img1), true);
		
		if (!writer)
		{
			fprintf(stderr, "\nVideoWriter failed!\n");
		}

		cvWriteFrame(writer, img1);
		cvWriteFrame(writer, img2);
		

		cvReleaseVideoWriter(&writer);
		cvReleaseImage(&img1);
		cvReleaseImage(&img2);
	}
}
