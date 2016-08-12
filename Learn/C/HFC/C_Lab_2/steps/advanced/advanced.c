#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <unistd.h>
#include <opencv/cxcore.h>
#include <errno.h>
#include <string.h>


//OpticalFlowFarneback variables:
double pyr_scale = 0.5;
int levels = 3;
int winsize = 5;
int iterations = 1;
int poly_n = 5;
double poly_sigma = 1.2;
int flags = 0;

float sum(const CvMat* mat);
void error(char* msg);
float simple_movement_calculation(IplImage* prev_frame, IplImage* frame, IplImage* gray_prev_frame, IplImage* gray_frame, CvMat* optical_flow);
float absolute_value(float s);

float simple_movement_calculation(IplImage* prev_frame, IplImage* frame, IplImage* gray_prev_frame, IplImage* gray_frame, CvMat* optical_flow)
{
	cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
	
	cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);

	// Calculate Farneback Optical Flow
	cvCalcOpticalFlowFarneback(gray_frame, gray_prev_frame, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
	float score = absolute_value(sum(optical_flow));
	
	return score;
}

// Error handling.
void error(char* msg)
{
	printf("%s: %s", msg, strerror(errno));
	exit(errno);
}

// Calculates the sum of the optical flow images individual vectors, which will be 
// used to determine how much movement there is between the images.
float sum(const CvMat* mat)
{
	float s = 0.0;
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

// Returns the absolute value.
// Differentiation between positive and negative vectors is not useful in the context of
// this project the way it is returned by the optical flow algorithm.
float absolute_value(float s)
{
	if(s >= 0)
		return s;
	else
		return -s;
}
	

int main()
{
	// Wait for the user to get away.
	sleep(1);
	
	// Window to show normal view & B&W view.
	cvNamedWindow("prev", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("next", CV_WINDOW_AUTOSIZE);
	
	// create CvCapture struct as a handle to the webcam - with error checking
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");
	
	// Getting the first frame.
	IplImage* prev_frame = cvQueryFrame(webcam);
	
	// Introduce lag to make the frames differ by a standard amount of time.
	// (33000μsec == 33msec == the standard time difference for video (I think :P))
	usleep(33);
	
	// Getting the next frame.
	IplImage* frame = cvQueryFrame(webcam);
	
	// Store the B&W version of the previous frame.
	IplImage* gray_prev_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	
	// Create the optical flow container.
	CvMat* optical_flow = cvCreateMat(frame->height, frame->width, CV_32FC2);
	
	// Store the B&W version of the next frame.
	IplImage* gray_frame = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 1);
	
	// The program terminates only via SIGINT (Ctrl^C) or error signals at this point.
	while(1)
	{	
		prev_frame = cvQueryFrame(webcam);
		float score = simple_movement_calculation(prev_frame, frame, gray_prev_frame, gray_frame, optical_flow);
		usleep(33);
		frame = cvQueryFrame(webcam);
		
		printf("%f\n", score);

		// Set the threshold for max movement*.
		// (*Threshold set based on observation and experimentation: the average result in
		// a loop with no (intentional) movement, over 20, 50, 100 iterations.)		
	    		
		if(score > 1300)
		{
			printf("\t\tYOU MOVED!!\n");
		}

		
		cvShowImage("prev", gray_prev_frame);
		cvShowImage("next", gray_frame);
	}
	
	cvDestroyWindow("prev");
	cvDestroyWindow("next");
	
	cvReleaseImage(&frame);
	cvReleaseImage(&gray_prev_frame);
	
	return 0;
}
