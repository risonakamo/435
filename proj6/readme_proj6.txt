compsci 435 proj 6
khang ngo
khang4@umbc.edu

description:
simple image seaming program

program description:
-takes in image and smaller dimensions and outputs a seamed image

usage:
-'make' to compile
-requires slvector to be in ../common
-executable name is seam
-'seam <input file> <output file> <new width> <new height>'
-note that it does pretty much no error checking on files
-only makes images smaller (new dimensions have to be smaller)

implementation notes:
-although i think i definitely used the energy function given in class,
my results look different from the ones on the website...didn't really know
what to do about that
-while testing on windows when running it says something about
"invalid parameter - <input file name>" and "invalid parameter - 100" or
something, and some other errors sometimes, I just ignored this, it still works
(i think its cimg being weird)
-inputs and outputs need correct jpg or png extension on them or cimg
freaks out

extra credit:
-webpage, accessible at https://risonakamo.github.io/435/proj6/website/
or just open the index.html in the website folder (prob won't work if
accessing on the gl server)
-btw: for some reason you need the slash at the end of the url

references:
pdf from proj description
wikipedia
not much this time