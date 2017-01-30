default: slVector.o slTransform.o
	ar cr libcommon.a slVector.o slTransform.o
	ranlib libcommon.a

%.o: %.cpp
	c++ -c -DNDEBUG -O3 -o $@ $< 
