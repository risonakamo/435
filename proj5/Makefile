ofiles=bird.o bs.o slVector.o

bird: $(ofiles)
	g++ $(ofiles) -o bird

bird.o: bird.c
	g++ -c bird.c

bs.o: bs.h bs.c
	g++ -c bs.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ bird.exe bird
