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
#include  <string.h> 
#include  <math.h> 
#include "rotutils.h"

int num_icosamp(int L)
{
    return (12 + L*30 + 20*(L-1)*L/2);
}

int num_unifsamp(int n)
{
    return (floor(((double) n*n) / M_PI));
}

int main (int argc, char * argv[])
{
    /* variable defs */
    int i = 0;
	int n1, n2;
	int totnum = 0; 
	int done = 0;
	int L = 0;
	int N;

    if (argc < 4)
    {
        fprintf(stderr,"Usage:  set_sizes  -eis  angdivs  outname  >  run_soi.sh  \n");
        exit(1);
    }

	/* are we sampling by angle or by number of rotations? */
	
	if (strchr(argv[1],'n') != NULL)
	{
		totnum = 1;
	}
	
	/* convert angle or number of rotations to parameters for various sampling schemes */
	
	if (strchr(argv[1],'e') != NULL)
	{
		fprintf(stderr,"Laura and Roummel, please fill this in \n");
	}
	else if (strchr(argv[1],'i') != NULL)
	{
		if (totnum == 0)
		{
			while (!done)
			{
				N = floor(5.675 * (double) (L+1));
				if (N >= atoi(argv[2]))
				{
					done = 1;
				}
				else
				{
					L++;
				}
			}

			n1 = N;
			n2 = L;  
		}
		else
		{
			while (!done)
			{
				N = ((int) floor(5.675 * (double) (L+1))) * num_icosamp(L);
				if (N >= atoi(argv[2]))
				{
					done = 1;
				}
				else
				{
					L++;
				}
			}
			
			n1 = (int) floor(5.675 * (double) (L+1));
			n2 = L;
		}
		
		printf("./sample_icosa %i > %s.xyz\n",n2,argv[3]);
		printf("./sample_soi %s.xyz %i > %s.eul\n",argv[3],n1,argv[3]);
		
	}
	else if (strchr(argv[1],'s') != NULL)
	{
		if (totnum == 0)
		{
			n1 = atoi(argv[2]);
			n2 = num_unifsamp(n1);  
		}
		else
		{
			while (!done)
			{
				N = L * num_unifsamp(L);
				if (N >= atoi(argv[2]))
				{
					done = 1;
				}
				else
				{
					L++;
				}
			}
			
			n1 = L;
			n2 = num_unifsamp(n1);  
		}
		
		printf("./sample_sphere %i > %s.xyz\n",n2,argv[3]);
		printf("./sample_soi %s.xyz %i > %s.eul\n",argv[3],n1,argv[3]);
	}
	else
	{
		fprintf(stderr,"You must specify one of the flags -e, -i or -s.\n");
		exit(1);
	}
} 



