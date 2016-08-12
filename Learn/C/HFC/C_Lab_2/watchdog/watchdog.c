#include <stdio.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>
#include <opencv/cv.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

//OpticalFlowFarneback variables:
typedef struct farneback_vars
{
	double pyr_scale;
	int levels;
	int winsize;
	int iterations;
	int poly_n;
	double poly_sigma;	
	int flags;
}farneback_vars;

void grab(IplImage* images[], int how_many, CvCapture* webcam);
void error(char* msg);
void set_default_farneback(farneback_vars* vars);
float sum(const CvMat* mat);
void dense_optical_flow_setup(IplImage* images[]);
float dense_optical_flow(IplImage* images[], CvMat* optical_flow, farneback_vars* vars);

void set_default_farneback(farneback_vars* vars)
{
	vars->pyr_scale = 0.5;
	vars->levels = 2;
	vars->winsize = 5;
	vars->iterations = 1;
	vars->poly_n = 5;
	vars->poly_sigma = 1.2;
	vars->flags = 0;
}


int main()
{
	usleep(10);
	
	CvCapture* webcam = cvCreateCameraCapture(0);
	if(webcam == NULL)
		error("Can't connect to camera");

	IplImage* images[4];
	grab(images, 4, webcam);

	farneback_vars vars;
	set_default_farneback(&vars);
	
	CvMat* optical_flow = cvCreateMat(images[0]->height, images[0]->width, CV_32FC2);
	dense_optical_flow(images, optical_flow, &vars);
	
	cvNamedWindow("1", CV_WINDOW_NORMAL);
	cvNamedWindow("2", CV_WINDOW_NORMAL);
	cvShowImage("1", images[1]);
	cvShowImage("2", images[3]);
	
	while(1)
	{
		grab(images, 4, webcam);
				cvShowImage("1", images[1]);
		cvShowImage("2", images[3]);
		float score = dense_optical_flow(images, optical_flow, &vars);
		printf("%.1f\n", score);

		if(score > 150000)
		{
			char path[50];
			strcpy(path,"sample.jpg");
			IplImage* evidence = cvQueryFrame(webcam);
			cvSaveImage(path, evidence, 0);
			printf("Gotcha!");
			return 0;
		}
	}
	
	return(-1);
}

// Fills an array with alternating frames and their B&W counterparts.
void grab (IplImage* images[], int how_many, CvCapture* webcam)
{
	how_many += 1;
	for(int i = 1; i < how_many; i++)
	{
		if(i%2 == 1)
		{
			images[i-1] = cvQueryFrame(webcam);
			images[i] = cvCreateImage(cvGetSize(images[i-1]), IPL_DEPTH_8U, 1);
			cvCvtColor(images[i-1], images[i], CV_RGB2GRAY);
			usleep(3300);
		}
	}
}

// Handles errno and displays an error.
void error(char* msg)
{
	fprintf(stderr, "%s %s", msg, strerror(errno));
	exit(0); 
}

float dense_optical_flow(IplImage* images[], CvMat* optical_flow, farneback_vars* vars)
{
	cvCalcOpticalFlowFarneback(images[1], images[3], optical_flow, vars->pyr_scale, vars->levels, vars->winsize, vars->iterations,
	vars->poly_n, vars->poly_sigma, vars->flags);
	
	return sum(optical_flow);
}

float sum(const CvMat* mat)
{
	float s =  0.0f;
	for(int row=0; row<mat->rows; row++)
	{
		const float* ptr = (const float*)(mat->data.ptr + row * mat->step); 
		for(int col=0; col<mat->cols; col++ )
		{
			s += *ptr++;
		}
	}
	if(s >= 0)
		return(s);
	else
		return(-s);
}