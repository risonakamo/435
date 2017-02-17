ofiles=rat.o slVector.o rayd2.o rayp.o

rat: $(ofiles)
	g++ $(ofiles) -o rat

rat.o: rat.c
	g++ -c rat.c

rayd2.o: rayd2.c rayd2.h
	g++ -c rayd2.c

rayp.o: rayp.c rayp.h
	g++ -c rayp.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ *.exe rat
