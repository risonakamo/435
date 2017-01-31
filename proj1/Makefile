in: in.o rayd.o pogn.o slVector.o
	g++ in.o rayd.o pogn.o slVector.o -o in

in.o: in.c
	g++ -c in.c

rayd.o: rayd.c rayd.h
	g++ -c rayd.c

pogn.o: pogn.c pogn.h
	g++ -c pogn.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ *.exe
