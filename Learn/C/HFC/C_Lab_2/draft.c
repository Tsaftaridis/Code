#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include "error_handling.h"

int main()
{
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	IplImage* image;
	
	if(webcam == NULL)
		error("Can't connect to webcam");
	
	while(1)
	{
		image = cvQueryFrame(webcam);

		
		if(image)
		{
			printf("Done!");
			IplImage *im_gray = cvCreateImage(cvGetSize(image),IPL_DEPTH_8U,1);
			cvCvtColor(image, im_gray, CV_RGB2GRAY);
			
			printf("too!");
			/*/process image
			printf("Got it!\n");
			cvCvtColor(image, previous, CV_RGB2GRAY);
			cvCvtColor(cvQueryFrame(webcam), image, CV_RGB2GRAY);
			cvCalcOpticalFlowFarneback(previous, image, flow, 0.5, 1, 5, 5, 7, 1.5,  0);*/
			return 0;
		}
		printf("MORE Shit\n");
	}
	
	// Clean up the webcam struct (stored in the heap)
	cvReleaseCapture(&webcam);
	
	// Clean up the other structs
	cvReleaseImage(&image);
	
	return 0;
}