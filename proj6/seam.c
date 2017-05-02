#define cimg_display 0

#include <iostream>

#include "pixl.h"
#include "CImg.h"
#include "../common/slVector.H"

using namespace cimg_library;

int main(int argc,char* argv[])
{
  if (argc<2)
  {
    std::cout<<"invalid input"<<std::endl;
    return 0;
  }

  CImg<double> inputimg(argv[1]);
  inputimg.RGBtoLab();

  pixl* pixls[inputimg.width()*inputimg.height()];

  int iheight=inputimg.height();
  int iwidth=inputimg.width();

  int i=0;
  for (int x=0;x<iwidth;x++)
  {
    for (int y=0;y<iheight;y++)
    {
      pixls[i]=new pixl(inputimg(x,y,0),inputimg(x,y,1),inputimg(x,y,2));
      i++;
    }
  }

  pixls[0]->printLab();

  return 0;
}