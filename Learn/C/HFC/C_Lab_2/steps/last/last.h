float sum(const CvMat* mat)
{
	printf("WHAT?-WHY?");
	float s =  0.0f;
	for(int row=0; row<mat->rows; row++ )
	{
		const float* ptr = (const float*)(mat->data.ptr + row * mat->step); 
		for(int col=0; col<mat->cols; col++ )
		{
			s += *ptr++;
		}
	}
	
	if(s >= 0)
		return s;
	else
		return -s;
}

double pyr_scale = 0.5;
int levels = 3;
int winsize = 5;
int iterations = 1;
int poly_n = 5;
double poly_sigma = 1.2;
int flags = 0;

float dense(IplImage* prev_frame, IplImage* frame, IplImage* gray_prev_frame, IplImage* gray_frame, CvMat* optical_flow)
{
	cvCvtColor(prev_frame, gray_prev_frame, CV_RGB2GRAY);
	cvCvtColor(frame, gray_frame, CV_RGB2GRAY);
	printf("RAN");
	cvCalcOpticalFlowFarneback(gray_frame, gray_prev_frame, optical_flow, pyr_scale, levels, winsize, iterations, poly_n, poly_sigma, flags);	
	
	return sum(optical_flow);
}