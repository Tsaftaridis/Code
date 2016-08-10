#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <unistd.h>
#include <opencv/cxcore.h>
#include "error_handling.h"
#include "advanced.h"

int main()
{
	// Wait for the user to get away.
	sleep(1);
	
	unsigned long int middle;
	
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
	
	// Create the optical flow container.
	CvMat* optical_flow = cvCreateMat(frame->height, frame->width, CV_32FC2);
	
	// Store the B&W version of the next frame.
	IplImage* gray_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	
	// The program terminates only via SIGINT (Ctrl^C) or error signals at this point.
	for(int shit = 0; shit < 20; shit++)
	{	
		float score = simple_movement_calculation(prev_frame, frame, gray_prev_frame, gray_frame, optical_flow);
		
		printf("%f\n", score);

		// Set the threshold for max movement*.
		// (*Threshold set based on observation and experimentation: the average result in
		// a loop with no (intentional) movement, over 20, 50, 100 iterations.)		
	    
	    middle += score;
	    		
		if(score > 20000)
		{
			printf("\t\tYOU MOVED!!\n");
		}
		
		// Get frame.
		prev_frame = cvQueryFrame(webcam);
		
		usleep(330);

		// Get the next frame and then do it all over again.
		frame = cvQueryFrame(webcam);
	}

	printf("\n\n\n%lu\n\n\n", middle/20);
	
	cvReleaseImage(&frame);
	cvReleaseImage(&gray_prev_frame);
	
	return 0;
}