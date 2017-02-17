#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayd2.h"
#include "rayp.h"

using namespace std;

int main(int argc,char* argv[])
{
  if (argc!=3)
    {
      cout<<"rat <input nff filename> <output ppm filename"<<endl;
      return 0;
    }
  
  rayp* bill=new rayp;
  bill->loadFile(argv[1],argv[2]);
  //  bill->printt();

  rayd2 bob(bill);
  bob.calcVec();
  bob.genPpoints();
  //  bob.printPars();
  bob.isect();
  
  return 0;
}
