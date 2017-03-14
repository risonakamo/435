ofiles=rats.o slVector.o rayp.o iobj.o rast.o

rats: $(ofiles)
	g++ $(ofiles) -o rats

rats.o: rats.c
	g++ -c rats.c

rayp.o: rayp.c rayp.h
	g++ -c rayp.c

iobj.o: iobj.c iobj.h
	g++ -c iobj.c

rast.o: rast.h rast.c
	g++ -c rast.c

slVector.o: ../common/slVector.H ../common/slVector.cpp
	g++ -c ../common/slVector.cpp

clean:
	rm -f *.o *~ *.exe rats
