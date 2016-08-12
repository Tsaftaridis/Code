/** Functions for the advanced code - a more organized version of the intruder code.
  * Developed as a solution to the Head First Cs C Lab #2.
  * Implements a 
  *
 */

// Calculates the sum of the optical flow images individual vectors, which will be 
// used to determine how much movement there is between the images.
float sum(const CvMat* mat)
{
	float s =  0.0f;
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
	
//OpticalFlowFarneback variables:
double pyr_scale = 0.5;
int levels = 3;
int winsize = 5;
int iterations = 1;
int poly_n = 5;
double poly_sigma = 1.2;
int flags = 0;

float simple_movement_calculation(IplImage* prev_frame, IplImage* frame, IplImage* gray_prev_frame, IplImage* gray_frame, CvMat* optical_flow)
{
	cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
	
	cvCvtColor(frame, gray_frame,  CV_RGB2GRAY);

	// Calculate Farneback Optical Flow
	cvCalcOpticalFlowFarneback(gray_frame, gray_prev_frame, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);
	float score = absolute_value(sum(optical_flow));
	
	return score;
}
