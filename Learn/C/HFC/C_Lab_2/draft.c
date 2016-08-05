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
			//cvNamedWindow("Grayscale-prev", CV_WINDOW_AUTOSIZE);
			//cvNamedWindow("Grayscale-next", CV_WINDOW_AUTOSIZE);
			//cvShowImage("Grayscale-prev", im_gray_prev);
			//cvWaitKey(0);
			//cvShowImage("Grayscale-next", im_gray_next);
			//cvWaitKey(0);
			//cvDestroyWindow("Grayscale-prev");			
			//cvDestroyWindow("Grayscale-next");
			
			//IplImage *flow = cvCreateImage(cvGetSize(im_gray_prev), CV_32FC3);
			cvMat* flow = cvCreateMat(prev->height, next->width, CV_32FC2);
			// Buggy code starts here:
			cvCalcOpticalFlowFarneback(im_gray_prev, im_gray_next, flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
			
			cvNamedWindow("Flow", CV_WINDOW_AUTOSIZE);
			cvShowImage("Flow", flow);
			cvWaitKey(0);
			//cvReleaseImage(flow);
			cvDestroyWindow("Flow");
			
			// Buggy code ends here.. Too tired to look into it...
			//cvCalcOpticalFlowFarneback(
			//cvCalcOpticalFlowFarneback((const CvArr* prevImg, const CvArr* nextImg, CvArr* flow, double pyrScale, int levels, int winsize, int iterations, int polyN, double polySigma, int flags¶);*/
			
			cvReleaseImage(&im_gray_prev);
			cvReleaseImage(&im_gray_next);
			return 0;
		}
	}
	
	// Clean up the webcam struct (stored in the heap)
	cvReleaseCapture(&webcam);
	
	// Clean up the other structs
	cvReleaseImage(&next);
	cvReleaseImage(&prev);
	
	return 0;
}