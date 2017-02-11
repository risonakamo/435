ofiles=in.o slVector.o rayd2.o rayp.o

in: $(ofiles)
	g++ $(ofiles) -o in

in.o: in.c
	g++ -c in.c

rayd2.o: rayd2.c rayd2.h
	g++ -c rayd2.c

rayp.o: rayp.c rayp.h
	g++ -c rayp.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ *.exe
