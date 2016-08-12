/*  intruder.c 
	
	Code written as a project for the book "Head First C", in "C Lab #2".
	Detects movement in the webcam feed and captures an image when a movement threshold is
	treaded.
 */

#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <unistd.h>
#include <opencv/cxcore.h>
#include "error_handling.h"
#include "intruder.h"

int main()
{
	// Wait for the user to get away.
	sleep(1);
	
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");
	
	// Getting the first frame.
	IplImage* prev_frame = cvQueryFrame(webcam);
	
	// Introduce lag to make the frames differ by a standard amount of time.
	// (33000μsec == 33msec == the standard time difference for video (I think :P))
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
	
	// The program terminates only via SIGINT (Ctrl^C) or error signals at this point.
	while(1)
	{	
		// Calculate Farneback Optical Flow
		cvCalcOpticalFlowFarneback(gray_frame, gray_prev_frame, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
		float score = absolute_value(sum(optical_flow));
		
		// Set the threshold for max movement*.
		// (*Threshold set based on observation and experimentation: the average result in
		// a loop with no (intentional) movement, over 20, 50, 100 iterations.)		
		if(score > 40000)
		{
			printf("\t\tYOU MOVED!!\n");
		}
		
		prev_frame = cvQueryFrame(webcam);
		cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
		
		// Get the next frame and then do it all over again.
		frame = cvQueryFrame(webcam);
		
		// The Farneback function needs the frames in B&W.
		cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);
	}


	cvReleaseImage(&frame);
	cvReleaseImage(&gray_prev_frame);
	
	return 0;
}