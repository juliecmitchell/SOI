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
#include "rotutils.h"

int main(int argc, char **argv)
{
    FILE     *ptsfile, *engfile;
    double   P[3];
    double   eng, escale;
	double   xscale = 1.0;
	double   emin, emax;
    int      numP;
    

    if (argc < 2)
    {
        printf("Usage:  pts2pdb   points.pts   >   points.pdb \n");
        return 0;
    }

    ptsfile = fopen(argv[1], "r");
		
	if (argc > 2) 
	{
		xscale = atof(argv[2]);
	}
    
	if (argc > 3) 
	{
		engfile = fopen(argv[3],"r");
		
		emin =  10000.0;
		emax = -10000.0;
		
		while (fscanf(engfile,"%lf",&eng))
		{
			if (eng > emax)
			{
				emax = eng;
			}
			
			if (eng < emin)
			{
				emin = eng;
			}
		}
		
		rewind(engfile);
	}

    numP = 0;
       
    while (fscanf(ptsfile,"%lf %lf %lf",&P[0], &P[1], &P[2]) == 3)
    {
		if (argc > 3) 
		{
			fscanf(engfile,"%lf",&eng);
			eng = 99.0 * ( (eng - emin) / (emax - emin) );
		} 
		else
		{
			eng = P[0] * 49 + 50;
		}

        printf("ATOM  %5d  FE  SOI %5d    %8.3lf%8.3lf%8.3lf  1.00 %5.2lf\n", numP+1, numP+1, xscale * P[0], xscale * P[1], xscale * P[2], eng);
        numP++;
    }
    
    fclose(ptsfile);

	if (argc > 3) 
	{
		fclose(engfile);
    }
	
    return 0;
}
