#define cimg_display 0

#include <iostream>

#include "CImg.h"
#include "../common/slVector.H"

using namespace cimg_library;

int main(int argc,char* argv[])
{
  CImg<double> inputimg(argv[1]);

  std::cout<<inputimg(0,115,0)<<std::endl;

  return 0;
}