#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "error_handling.h"
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <stdlib.h>
#include <opencv/cxcore.h>
#include "last.h"

float limit = 10000;




int main()
{	
	printf("FUCK!");
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");
		
	IplImage* prev_frame = cvQueryFrame(webcam);
	
	IplImage* frame = cvQueryFrame(webcam);
	
	IplImage* gray_prev_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
	IplImage* gray_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);
	
	printf("67");
	CvMat* optical_flow = cvCreateMat(frame->height, frame->width, CV_32FC2);
	
	float score;
	
	while(1)
	{	
		score = dense(prev_frame, frame, gray_prev_frame, gray_frame, optical_flow);
		
		printf("Score: %f", score);
		
		if(score > limit)
		{
			printf("\nGotcha!\n");
			return 0;
		}
		
		prev_frame = cvQueryFrame(webcam);
		
		usleep(33000);
		
		frame = cvQueryFrame(webcam);
	}

	cvReleaseImage(&frame);
	cvReleaseImage(&gray_prev_frame);
	
	return 0;
}