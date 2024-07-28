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

#define ZERO 0.000000000000001

/* typedefs */
typedef double vec[3];
typedef int edge[2];
typedef int sim[3];

/* input and output */
int LOAD_EA(char *filename, double **M);
int LOAD_QUAT(char *filename, double **M);
int LOAD_PTS(char *filename, double **M);
void PRINTVEC(vec v);

/* convert input to matrices */
void QUAT_MAT(double *M, double *q);
void EA_MAT(double *M, double *E);
void AA_MAT(vec ax, double ang, vec *R);
void VV_MAT(vec vec1, vec vec2, vec *R);

/* matrix distances and metrics */
double MAT_DIST(double *M, double* N);
double PROJ_DIST(double *M, double* N);

/* matrix/vector manipulation */
void CROSS(vec v, vec w, vec vxw);
void MMULT (vec *Left, vec *Right, vec *R);
void ROTATE (vec *R, vec v);
void NORMAL(vec v);

/* tools for analyzing rotation samples */
void COVERAGE(double **M, int numM, double **RM, int numRM, double *minDist);
void SEPARATION(double **M, int numM, double *minDist, double *minminDist, double *maxminDist); 
void CALC_ENG(int numM, double **M, int numP, double *P, double *E) ;
 
