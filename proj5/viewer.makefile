viewer: slVector.o viewer.o
	c++ viewer.o slVector.o -O3 -Wno-deprecated -lglut32win -lopengl32 -lglu32 -o viewer

slVector.o: ../common/slVector.H ../common/slVector.cpp
	c++ -c ../common/slVector.cpp

viewer.o: viewer.cpp
	c++ -c -lglut32win -lopengl32 -lglu32 viewer.cpp

clean:
	rm -f *.o *~ *.exe viewer
