/** Functions for the intruder code.
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
// this project, the way it is returned by the optical flow algorithm.
float absolute_value(float s)
{
	if(s >= 0)
		return s;
	else
		return -s;
}

