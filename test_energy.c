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
    FILE     *rotfile, *outfile;
    int     i,j,k,numM,numP;
    double    Energy, dist, p;
    int        mode;
    double   **M, *E, *P, in[5];
    char     inStr[120];
    
    if  (argc != 2)
    {
        printf("Usage:  test_energy   rotfile  >  outfile\n");
        return 0;
    }

    rotfile = fopen(argv[1], "r");

    numM = 0;
    
    /* allocate data storage */
    
    rotfile = fopen(argv[1],"r");
    while (fgets(inStr,120,rotfile))
    {
    	numM++;
    }
    fclose(rotfile);
    
    mode = sscanf(inStr,"%lf %lf %lf %lf %lf",&in[0],&in[1],&in[2],&in[3],&in[4]);
        
    M = (double **) malloc(numM * sizeof(double *));
    for (i=0; i<numM; i++)
    {
    	M[i] = (double *) malloc(9 * sizeof(double));
    }
    
    numP = 10;
    
    E = (double *) malloc(numP * sizeof(double));
    P = (double *) malloc(numP * sizeof(double));
    
    /* Read in the sampled rotations */
    
    if (mode == 3)
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
        fprintf(stderr,"Format problem:  use Euler angles or quaternions.  \n");
    }
        
    fprintf(stderr,"numRots: %i\n",numM);
    
    /* calculate repulsive energy for of various orders */
    
    P[0] = 0.25;           P[1] = 0.33;           P[2] = 0.5;
    P[3] = 1.0;            P[4] = 2.0;            P[5] = 3.0;
    P[6] = 4.0;            P[7] = 6.0;            P[8] = 9.0;
    P[9] = 12.0;
    
    CALC_ENG(numM, M,numP, P, E);
    
    printf("%15s %15s %15s %15s %15s %15s %15s %15s %15s %15s\n","p=1/4","p=1/3","p=1/2","  p=1","  p=2","  p=3","  p=4","  p=6","  p=9"," p=12");
    printf("%15.6g %15.6g %15.6g %15.6g %15.6g %15.6g %15.6g %15.6g %15.6g %15.6g\n",E[0],E[1],E[2],E[3],E[4],E[5],E[6],E[7],E[8],E[9]);
    
    /* free memory */
    
    for (i=0; i<numM; i++)
    {        
        free(M[i]);        
    }
    free(M);    
    free(E);
    free(P);
    
    return 0;
}
