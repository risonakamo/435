compsci 435 proj 3
khang ngo
khang4@umbc.edu

description:
rasteriser handling basic nff files

program description:
-rayp object parses file just like with ray tracer
-rast takes data and does math

usage:
-'make' to compile
-requires slvector to be in ../common
-executable name is rats
-'rats <input nff file> <output nff file>'
-note that it does pretty much no error checking on files

implementation notes:
(for if you read my code)
-data arrays in the iobj which represents triangles are stored
as 1d arrays for 3 points in order, but the ray tracer used
the same thing so shouldn't be too weird

extra credit:
-_-

references:
textbook
website slides
http://web.eecs.utk.edu/~huangj/cs456/notes/456_rasterization.pdf
https://codeplea.com/triangular-interpolation
http://www.inf.ed.ac.uk/teaching/courses/cg/lectures/slides7.pdf
https://courses.cs.washington.edu/courses/cse455/09wi/Lects/lect5.pdf
http://www.cse.psu.edu/~rtc12/CSE486/lecture12.pdf
