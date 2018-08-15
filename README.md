# image-manipulator
2-part phase academic project that takes as input a ppm image. During first part we convert the image to it's negative. During second part we add filters.

Genral instructions for the project execution

1) The project can be run on Visual Studio 2015 and later.
2) The main functionality of reading the binary characters and writing them again is being developed in ppm_library for future reuse.
3) Make a clean before build :)

Instructions for executing the first project

-> Write in the console : neg photosample.ppm

Instructions for executing the second project

-> Write in the console : filter -f gamma 2.0 -f linear -1 -1 -1 1 1 1 sampleImage.ppm
*The first filter defines the linear and the second gamma filter
*The 2nd project has some problems during filtering which i am commited to fix in the near future.

Generally the skills we demonstrated are : 

1) Creating and managing libraries.
2) Dynamic allocation and deallocation of memory
3) Pointer usage
4) Reading and writing to files
5) Templates usage
6) Object oriented programming
