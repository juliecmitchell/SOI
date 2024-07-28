# SOI
These codes can be used to generate uniform samples of spheres, ellipsoids and
rotation groups.  They are distributed as-is with no intended warranty or guarantee
of suitability for any purpose.  

HOW TO INSTALL AND RUN:
  
   1. Go into the source directory  ( cd src )

   2. Run the makefile ( make install )
       - it may be necessary to change the name of your compiler, so 
         try replacing "cc" with "gcc" if you get an error.

   3. Move to the bin directory ( cd ./bin ) 

   4. Type the name of a program ( ./sample_icosa )
       - this will tell you the program call to use

CITATION:

JC Mitchell (2008) Sampling Rotation Groups by Successive Orthogonal Images. SIAM Journal on Scientific Computing, vol. 30, issue 1, pp. 525-547. https://doi.org/10.1137/03060187

LIST OF PROGRAMS:

* Tools for generating samples of spheres, ellipsoids and rotation spaces

  sample_icosa - quickly generates a sphere sample using angular subdivision
    of an icosahedron.
	
  sample_sphere - generates a distributed sphere sample by minimizing repulsive
    energies.
	
  sample_ellipsoid - generates a uniform sample on spheres or ellipsoids using
    a variable stepping approach.  


* Tools for checking the quality of rotation samples
  
  test_separation - returns the nearest neighbor distance for each element
    of a rotation sample.

  test_coverage - returns the maximum random nearest neighbor distance for
    each element of a rotation sample.
	
  test_energy - returns repulsive energies for the rotation sample.  
  

* Things you probably won't need and are mainly for the server

  normalize - turns a list of vectors into unit vectors 
  
  pts2pdb - turns a list of points into a pdb file

