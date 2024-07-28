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

#include  <stdlib.h> 
#include  <stdio.h> 
#include  <math.h> 
#include "rotutils.h"

int main (int argc, char * argv[])
{
    /* variable defs */
    int i = 0;
    double  s, w[3];        /* current point from vector list */
    double  alpha;          /* increment angle for rotation sample */
    double  angles[3];      /* ordered angles */
    int n;         		    /* number of angular divisions */
    FILE *inFile;


    if (argc < 3)
    {
        fprintf(stderr,"Usage:  sample_soi   points.pts   orthogonal_divisions \n");
        exit(1);
    }

	inFile = fopen(argv[1],"r");
	n = atoi(argv[2]);
	if (n  <  1)
	{
		n = 1;
	}
	alpha = 2.0 * M_PI/((double) n);
	
    while(fscanf(inFile, "%lf %lf %lf", &w[0], &w[1], &w[2]) == 3)
    {
         
		if (w[2] > 1.0)
		{
			w[2] = 1.0;
		}
		
		if (w[2] < -1.0)
		{
			w[2] = -1.0;
		}

        angles[1] = acos(w[2]);
 
		// printf("%lf %lf %lf %lf\n",w[0],w[1],w[2],angles[1]);
        if (angles[1] == 0.0)
        {
			angles[2] = 0.0;
        }
        else
        {
			s = -w[0]/sin(angles[1]);
			if (s > 1.0)
			{
				s = 1.0;
			}
			
			if (s < -1.0)
			{
				s = -1.0;
			}
			
            angles[2] = acos(s);

            if(w[1] < 0)
            {
                angles[2] = 2.0 * M_PI - angles[2];
            }
        }
        if (angles[2]  >  M_PI)
        {
            angles[2] += - 2.0 * M_PI;
        }
       
        for (i=0; i<n; i++ )
        {
            angles[0] = - M_PI + i * alpha;
            fprintf(stdout, "%14.10lf\t %14.10lf\t %14.10lf\n", angles[0], angles[1], angles[2]);
        }
    }

    return 0;
} 
