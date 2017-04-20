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
  // bob.printVecs();

  bob.run();
  // bob.treeTest();
}
