compsci 435 proj 5
khang ngo
khang4@umbc.edu

description:
simple bird boid system simulator

program description:
-takes in file and produces output file usable with viewer

usage:
-'make' to compile
-requires slvector to be in ../common
-executable name is birds
-'birds <input file name> <output file>'
-note that it does pretty much no error checking on files

implementation notes:
-i used the given kdtree, but apparently we have to rebuild the tree
each time, so it might not really be faster than checking every distance
-the viewer files and viewer-related stuff were for compiling/using viewer
on windows

extra credit:
-feeding

references:
pdf from proj description
http://www.cs.cmu.edu/afs/cs/academic/class/15462-s10/www/lec-slides/Lecture24_flocking.pdf
http://particleflocker.com/index.php/home/collision
https://web.cs.wpi.edu/~gogo/courses/mingw/