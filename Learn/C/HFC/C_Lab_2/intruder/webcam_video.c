#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include "error_handling.h"
int main()
{
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");
	
	cvNamedWindow("Frame", CV_WINDOW_AUTOSIZE);
	IplImage* frame = cvQueryFrame(webcam);	
	
	while(1)
	{		
		cvShowImage("Frame", frame);

		char c = cvWaitKey(33);
		
		if(c == 27)
			break;		
		

		frame = cvQueryFrame(webcam);
	}
	
	cvReleaseImage(&frame);
	
	cvDestroyWindow("Frame");
	return 0;
}
