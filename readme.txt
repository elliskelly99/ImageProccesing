This software is architectured as follows. This software can work on grad server.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image.
	utility- this folder hosts the files that students store their implemented algorithms.
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make

As a result you should get iptool in project/bin directory.

*** FUNCTIONS ***

1. Add intensity: add
Increase the intensity for a gray-level image.

2. Binarization: binarize
Binarize the pixels with the threshold.

3. Scaling: Scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.

4.) colorvisual: 
p1- threshold, p2-V1

*** PARAMETERS FILE ***

There are for parameters:
1. the input file name;
2. the output file name;
3. the name of the filter. Use "add", "binarize", and "scale" for your filters;
4. the value for adding intensity, threshold value for binarize filter, or the scaling factor for scale filter.


input as: ipf opf #roi x1 y1 Sx1 Sy1 func p1 p2 pX x2 y2 Sx2 Sy2 func p1 p2 pX
---------------------------------------------------------------------------------
oipf - name of original input image  
oopf- name of new modified output image 
ofunc- function name to be applied 
ox - initial row, this means the first pixel in the leftmost position to begin the ROI 
calculation 
oy - initial column, this means the first pixel in the top most position to begin the ROI 
calculation. Unlike x (which determines left to right), y axis is responsible for  up and 
down.   
oSx - total number of pixels in the x axis 
oSy - total number of pixels in the y axis 
op1, ...pX - parameters needed for function. Can range from 1 parameter through X 
number parameters depending on the function.  

*** Run the program: ./iptool parameters.txt
ignore seg fault will still print out images
