/* Intermediate file towards intruder.c 
   Makefile the same as intruder but with a different target and source file.
   Compiles, runs and displays two windows with images, one of which is lagging.
   Problems: The windows are reversed (the prev window is showing the newer frame).
   Not smooth.
 */

#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <unistd.h>
#include <opencv/cxcore.h>
#include "error_handling.h"

float sum(const CvMat* mat)
{
	float s =  0.0f;
	for(int row=0; row<mat->rows; row++ )
	{
		const float* ptr = (const float*)(mat->data.ptr + row * mat->step); 
		for(int col=0; col<mat->cols; col++ )
		{
			s += *ptr++;
		}
	}
	return(s);
}

unsigned long int middle = 0;

float absolute_value(float s)
{
	if(s >= 0)
		return s;
	else
		return -s;
}

int main()
{
	sleep(5);
	
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");
	
	// Window to show normal view & B&W view.
	//cvNamedWindow("B&W Frame", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("B&W Previous Frame", CV_WINDOW_AUTOSIZE);
	
	// Getting the first frame.
	IplImage* prev_frame = cvQueryFrame(webcam);
	
	// Introduce lag.
	usleep(33000);
	
	// Getting the next frame.
	IplImage* frame = cvQueryFrame(webcam);
	
	// Store the B&W version of the previous frame.
	IplImage* gray_prev_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
	
	// Store the B&W version of the next frame.
	IplImage* gray_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);
	
	// Create the optical flow container.
	CvMat* optical_flow = cvCreateMat(frame->height, frame->width, CV_32FC2);
	
	//OpticalFlowFarneback variables:
	double pyr_scale = 0.5;
	int levels = 3;
	int winsize = 5;
	int iterations = 3;
	int poly_n = 7;
	double poly_sigma = 1.5;
	int flags = 0;
	
	int shit;
	
	for(shit = 0; shit < 100; shit++)
	{	
		// Calculate Farneback Optical Flow
		cvCalcOpticalFlowFarneback(gray_frame, gray_prev_frame, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
		float score = absolute_value(sum(optical_flow));
		//printf("%.1f\n", score);
		
		if(score > 15000)
		{
			printf("\t\tYOU MOVED!! %d\n", shit);
		}
		
		middle += score;
		
		prev_frame = cvQueryFrame(webcam);
		cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
		
		// Give the user a chance to interrupt, while spacing the frames so as to get more
		// consistent results. (The frames are ~33 ms apart).
		char c = cvWaitKey(33);
		if(c == 27)
			break;
		
		// Get the next frame and then do it all over again.
		frame = cvQueryFrame(webcam);
		
		// The Farneback function needs the frames in B&W.
		cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);
		
		// Display the current frame.	
		//cvShowImage("B&W Frame", gray_frame);
		
		// Display the previous frame, while testing the gray_prev_frame variable.
		//cvShowImage("B&W Previous Frame", gray_prev_frame);
		
	}
	
	printf("Average: %lu\n", middle/shit);
	cvReleaseImage(&frame);
	cvReleaseImage(&gray_prev_frame);
	
	//cvDestroyWindow("B&W Frame");
	//cvDestroyWindow("B&W Previous Frame");
	return 0;
}