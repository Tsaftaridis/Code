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
			cvNamedWindow("Grayscale-prev", CV_WINDOW_AUTOSIZE);
			cvNamedWindow("Grayscale-next", CV_WINDOW_AUTOSIZE);
			cvShowImage("Grayscale-prev", im_gray_prev);
			cvWaitKey(0);
			cvShowImage("Grayscale-next", im_gray_next);
			cvWaitKey(0);
			cvReleaseImage(&im_gray_prev);
			cvReleaseImage(&im_gray_prev);
			cvDestroyWindow("Grayscale-prev");			
			cvDestroyWindow("Grayscale-next");
			
			// Buggy code starts here:
			IplImage *flow = cvCreateImage(cvGetSize(prev), IPL_DEPTH_8U, 3);
			IplImage *flowGray = cvCreateImage(cvGetSize(prev), IPL_DEPTH_8U, 3);
			cvCvtColor(flow,flowGray,CV_RGB2GRAY ); 

			cvCalcOpticalFlowFarneback(im_gray_prev, im_gray_next, flow, 0.5, 1, 5, 5, 7, 1.5, 0);
			// Buggy code ends here.. Too tired to look into it...
			//cvCalcOpticalFlowFarneback(
			//cvCalcOpticalFlowFarneback(previous, image, flow, 0.5, 1, 5, 5, 7, 1.5,  0);*/
			//return 0;
		}
	}
	
	// Clean up the webcam struct (stored in the heap)
	cvReleaseCapture(&webcam);
	
	// Clean up the other structs
	cvReleaseImage(&next);
	cvReleaseImage(&prev);
	
	return 0;
}