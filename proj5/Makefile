ofiles=bs.o slVector.o birds.o kdTree.o

birds: $(ofiles)
	g++ $(ofiles) -o birds

bs.o: bs.h bs.c
	g++ -c bs.c

birds.o: birds.c
	g++ -c birds.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

kdTree.o: kdTree.cpp kdTree.H
	g++ -c kdTree.cpp

clean:
	rm -f *.o *~ birds.exe birds
