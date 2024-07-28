/*****************************************************************************
 MIT License

 Copyright (c) 2007 Julie C. Mitchell and the University of Wisconsin

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
**************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <memory.h>
#include "rotutils.h"

/****************************************************************************
* Author: Julie Mitchell
* Function: ldist (main)
* Last Revision: 3/21/06
*
*  Calculates the least distance between each rotation and others in a sample
*
*  Usage:
*
*************************************************************************** */

int main(int argc, char **argv)
{    
    FILE     *myfile;
    int        i, j, mode, numM;
    double   minminDist,maxminDist;
    double   *minDist, **M, in[5];
    char	 inStr[120];
        
    if (argc < 2)
    {
        fprintf(stderr,"Usage:  test_separation  rotfile  >  outfile \n");
        exit(1);
    }


    numM = 0;
    
    /* allocate data storage */
    
    myfile = fopen(argv[1],"r");
    while (fgets(inStr,120,myfile))
    {
    	numM++;
    }
    fclose(myfile);
    
    mode = 2; //sscanf(inStr,"%lf %lf %lf %lf %lf",&in[0],&in[1],&in[2],&in[3],&in[4]);
    
    minDist = (double *) malloc(numM * sizeof(double));
    
    M = (double **) malloc(numM * sizeof(double *));
    for (i=0; i<numM; i++)
    {        
        M[i] = (double *) malloc(9 * sizeof(double));
        for (j=0; j<9; j++)
        {
        	M[i][j] = 0.0;
		}
    }
        
    /* Read in the sampled rotations */
    
    if (mode == 2)
    {
        /* points format */
        numM = LOAD_PTS(argv[1],M);
    }    
    else if (mode == 3)
    {
        /* Euler angle format */
        numM = LOAD_EA(argv[1],M);
    }    
    else if (mode == 4)
    {
        /* quaternion format */
        numM = LOAD_QUAT(argv[1],M);
    }
    else  
    {
        fprintf(stderr,"Format problem:  input points, Euler angles or quaternions.  \n");
    }
        
    fprintf(stderr,"numRots: %i\n",numM);
    
    /* calculate separation */
    
    SEPARATION(M,numM,minDist,&minminDist,&maxminDist);
        
    fprintf(stderr,"Minimum distance = %lf         Maximum minimum distance = %lf\n",minminDist,maxminDist);
    
    /* free memory */
    
    free(minDist);
    
    for (i=0; i<numM; i++)
    {
        free(M[i]);
    } 
    free(M);
    
    return 0;
}
