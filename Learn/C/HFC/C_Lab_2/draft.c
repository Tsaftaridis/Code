#include <stdio.h>
#include <opencv/cv.h>
#include <unistd.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "error_handling.h"

int main()
{
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	IplImage* prev, *next;
	
	//OpticalFlowFarneback variables:
	double pyr_scale = 0.5;
	int levels = 3;
	int winsize = 5;
	int iterations = 3;
	int poly_n = 7;
	double poly_sigma = 1.5;
	int flags = 0;
	
	if(webcam == NULL)
		error("Can't connect to webcam");
	
	while(1)
	{
		prev = cvQueryFrame(webcam);
		sleep(1);
		next = cvQueryFrame(webcam);
		
		if(prev && next)
		{
			IplImage *im_gray_prev = cvCreateImage(cvGetSize(prev),IPL_DEPTH_8U,1);
			IplImage *im_gray_next = cvCreateImage(cvGetSize(next), IPL_DEPTH_8U,1);
			cvCvtColor(prev, im_gray_prev, CV_RGB2GRAY);
			cvCvtColor(next, im_gray_next, CV_RGB2GRAY);
			
			
			CvMat* optical_flow = cvCreateMat(prev->height, next->width, CV_32FC2);
			
			cvCalcOpticalFlowFarneback(im_gray_prev, im_gray_next, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);

			float s = 0.0f;
			int i, j;
			for(i = 0; i < optical_flow->rows; i++)
			{
				const float* ptr = (const float*)(optical_flow->data.ptr + i * optical_flow->step);
				for(j = 0; j < optical_flow->cols; j++)
				{
					s += *ptr++;
				}
			}
			
			printf("Total movement score %f\n", s);
			
			cvReleaseImage(&im_gray_prev);
			cvReleaseImage(&im_gray_next);
		}
	}
	
	// Clean up the webcam struct (stored in the heap)
	cvReleaseCapture(&webcam);
	
	// Clean up the other structs
	cvReleaseImage(&next);
	cvReleaseImage(&prev);
	
	return 0;
}