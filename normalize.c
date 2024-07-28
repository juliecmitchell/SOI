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
    FILE     *ptsfile;
    double   P[3];
    double   temp;
    int      numP;
    

    if (argc != 2)
    {
        printf("Usage:  normalize   points.pts   >   points.uvec \n");
        return 0;
    }

    ptsfile = fopen(argv[1], "r");
    
    numP = 0;
       
    while (fscanf(ptsfile,"%lf %lf %lf",&P[0], &P[1], &P[2]) == 3)
    {
    		NORMAL(P);
		printf("%15.10lf %15.10lf %15.10lf\n",P[0], P[1], P[2]);
    }
    
    fclose(ptsfile);
    
    return 0;
}
