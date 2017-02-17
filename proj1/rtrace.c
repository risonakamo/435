/*rat.c RAy Trace
  driver program
  uses rayp and rayd to raytrace input file
  needs to be provided input file and ouput name*/

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
  //default if output name not provided
  string oname="output.ppm";
  if (argc>3 ||  argc<2)
    {
      cout<<"rat <input nff filename> <output ppm filename"<<endl;
      return 0;      
    }
  
  if (argc==3)
    {
      oname=argv[2];
    }
  
  rayp* data=new rayp;
  data->loadFile(argv[1],oname);

  rayd2 trace(data);
  trace.calcVec();
  trace.genPpoints();
  trace.isect();
  
  return 0;
}
