/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
    ComplexNumber * Z = newComplexNumber(0,0);

    ComplexNumber * Zsqr = ComplexProduct(Z,Z);

    ComplexNumber * result = ComplexSum(Zsqr,point);

    int counter = 1;
    // printf("---------------------------------------------------------\n");
    // printf("Threshold  = %f\n", threshold);
    // printf("Max iters = %llu\n", maxiters);
    // printf("Current C = (%f , %f) \n", Re(point),Im(point));
    // printf("Starting M = (%f , %f) \n", Re(result),Im(result));
    // printf("|M| = %f \n",ComplexAbs(result));
    //printf("current C = (%f , %f) \n", Re(point),Im(point));
    while(ComplexAbs(result) < threshold)
    {
        // printf("-------------------------------------------------------\n");
    	if(counter > maxiters)
        {
            //printf("Counter exceeded maxIters, returning 0\n");
    		return 0;
        }
         //printf("current C = (%f , %f) \n", Re(point),Im(point));
        // printf("current Z = (%f , %f) \n", Re(Z),Im(Z));
        ComplexNumber * temp = ComplexProduct(result,result);
        free(result);
    	result = ComplexSum(temp,point);
        free(temp);
        // printf("Current M = (%f , %f) \n", Re(result),Im(result));
        // printf("|M| = %f \n",ComplexAbs(result));
        // printf("counter = %d\n", counter);
    	counter ++;
    }
    //printf("|M| exceeded threshold, returning %d\n", counter);

    free(Z);
    free(result);
    free(Zsqr);
  	return counter;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.	
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output)
{
    //YOUR CODE HERE

    // center = newComplexNumber(5,3);
    // resolution = 2;

    //------------------------------------------- Test Area -------------------------------------------------------------------


    double step = scale/resolution;
    //printf("Step = %f\n", step);

    ComplexNumber * point = newComplexNumber(Re(center)-step*resolution,Im(center)+step*resolution);

    double initialRe = Re(center)-step*resolution;

    //printf("Starting point = (%f , %f) \n", Re(point),Im(point));

    output[0] = MandelbrotIterations(max_iterations,point,threshold);
    
    int rowSize = (2 * resolution + 1);
    //printf("Square size = %d * %d\n",rowSize, rowSize);
    for (int i = 1; i < rowSize*rowSize; i++)
    {
            if(i%rowSize == 0)
            {
                //printf("\n i = %d\n -----------------------------------------------------------New Row-------------------------------------------------------\n",i);
                point = newComplexNumber(initialRe,Im(point)-step);
            }
            else
            {
                point = newComplexNumber(Re(point) + step,Im(point));   
            }

            //printf("Current point = (%f , %f) \n", Re(point),Im(point));
            output[i] = MandelbrotIterations(max_iterations,point,threshold);
    }







//---------------------------------------------------------- New Code-----------------------------------------------------
    free(point);
}


