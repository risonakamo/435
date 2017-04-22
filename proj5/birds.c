/*birds.c - boids simulator driver
  khang ngo
  cmsc 435 proj 5
  driver program for boids system.  utilises the bs
  object.*/

#include <iostream>
#include <string>

#include "bs.h"

using namespace std;

int main(int argc,char* argv[])
{  
  string ofile="output.out";
  
  if (argc<2)
  {
    cout<<"invalid number of arguments"<<endl;
    cout<<"birds <input file> <[output file]>"<<endl;
    return 0;
  }

  if (argc==2)
  {
    cout<<"using default output file \"output.out\""<<endl;
  }

  else
  {
    ofile=argv[2];
  }

  bs bob(argv[1],ofile);

  bob.printPars();

  bob.run();
}
