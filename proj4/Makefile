ofiles=mfair.o io.o slVector.o sVtex.o

mfair: $(ofiles)
	g++ $(ofiles) -o mfair

mfair.o: mfair.c
	g++ -c mfair.c

io.o: io.cpp io.H
	g++ -c io.cpp

sVtex.o: sVtex.c sVtex.h
	g++ -c sVtex.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ *.exe mfair
