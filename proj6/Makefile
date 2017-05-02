ofiles=slVector.o seam.o pixl.o

seam: $(ofiles)
	g++ $(ofiles) -o seam

seam.o: seam.c CImg.h
	g++ -c seam.c

pixl.o: pixl.c pixl.h
	g++ -c pixl.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *~ *.o seam.exe seam
