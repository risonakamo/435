/*rats.c - rasteriser main
 khang ngo
 cmsc 435 proj3
 main driver for rasteriser.  pretty much the same
 as ray tracer's rat from proj2*/

using namespace std;

#include <iostream>
#include <cmath>
#include <string>

#include "../common/slVector.H"
#include "rast.h"
#include "rayp.h"

int main(int argc,char* argv[])
{
  //default if output name not provided
  string oname="output.ppm";
  if (argc>3 ||  argc<2)
    {
      cout<<"rats <input nff filename> <output ppm filename>"<<endl;
      return 0;      
    }
  
  if (argc==3)
    {
      oname=argv[2];
    }
  
  else
    {
      cout<<"using default output file name: output.ppm"<<endl;
    }
  
  rayp* data=new rayp;
  data->loadFile(argv[1],oname);
  data->printd();
  /* data->printad(); */

  rast rasteriser(data); 

  rasteriser.calcVec();
  rasteriser.rasterise();
  
  return 0;
}
