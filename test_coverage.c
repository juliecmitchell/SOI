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

int main(int argc, char **argv)
{
    FILE     *rotfile, *randfile;
    int     i,j;
    int        mode, numM, numRM=0;
    double   minminDist, maxminDist;
    double   *minDist, **M, **RM, in[5];
    char     inStr[120];
        
    if (argc < 2)
    {
        fprintf(stderr,"Usage:  test_coverage  rotfile  randfile  >  outfile \n");
        exit(1);
    }

    /* allocate data storage */
    
    numM = 0;
    rotfile = fopen(argv[1],"r");
    while (fgets(inStr,120,rotfile))
    {
    	numM++;
    }
    fclose(rotfile);
    
    mode = sscanf(inStr,"%lf %lf %lf %lf %lf",&in[0],&in[1],&in[2],&in[3],&in[4]);
    
    minDist = (double *) malloc(numM * sizeof(double));
    
    M = (double **) malloc(numM * sizeof(double *));
    for (i=0; i<numM; i++)
    {       
        M[i] = (double *) malloc(9 * sizeof(double));
    }
        
    numRM = 0;
    randfile = fopen(argv[2],"r");
    while (fgets(inStr,120, randfile))
    {
    	numRM++;
    }
    fclose(randfile);
    
    RM = (double **) malloc(numRM * sizeof(double *));   
    for (i=0; i<numRM; i++)
    {        
        RM[i] = (double *) malloc(9 * sizeof(double));
    }
       
    /* Read in the random rotations */
    
    numRM = LOAD_EA(argv[2],RM);
    
    /* Read in the sampled rotations */
    
    if (mode == 3)
    {        
        numM = LOAD_EA(argv[1],M);       
    }   
    else if (mode == 4)
    {       
        numM = LOAD_QUAT(argv[1],M);        
    }
    else  
    {
        fprintf(stderr,"Format problem:  use Euler angles or quaternions.  \n");
    }
        
    fprintf(stderr,"numRots: %i   numRand: %i\n",numM,numRM);
    
    COVERAGE(M, numM, RM, numRM, minDist);
    
    for (i=0;i<numRM;i++)
    {       
        printf("%15.6f \n",minDist[i]);
    }
          
    /* free memory */
    
    free(minDist);
    
    for (i=0; i<numM; i++)
    {        
        free(M[i]);
    }   
    
    free(M);
    
    for (i=0; i<numRM; i++)
    {       
        free(RM[i]);
    }
       
    free(RM);
    
    return 0;
}
