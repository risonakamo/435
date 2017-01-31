in: in.o rayd.o pogn.o
	g++ in.o rayd.o pogn.o -o in

in.o: in.c
	g++ -c in.c

rayd.o: rayd.c rayd.h
	g++ -c rayd.c

pogn.o: pogn.c pogn.h
	g++ -c pogn.c

clean:
	rm -f *.o *~ *.exe
