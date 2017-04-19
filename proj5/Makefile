ofiles=birds.o bs.o slVector.o bird.o kdTree.o

birds: $(ofiles)
	g++ $(ofiles) -o birds

birds.o: birds.c
	g++ -c birds.c

bs.o: bs.h bs.c
	g++ -c bs.c

bird.o: bird.h bird.c
	g++ -c bird.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

kdTree.o: kdTree.cpp kdTree.H
	g++ -c kdTree.cpp

clean:
	rm -f *.o *~ birds.exe birds
