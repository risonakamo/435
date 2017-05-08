#ifndef SEAM_H
#define SEAM_H

#define cimg_display 0

#include <iostream>
#include <cmath>

#include "pixl.h"
#include "CImg.h"
#include "../common/slVector.H"

using namespace cimg_library;

class seam
{
 public:
  seam();
  seam(char* inputfile); //constructor builds pixl array

  void resize(int width,int height,const char* ofile);

  /*-- debug --*/
  void printEnergy(); //print all energies

 private:
  void calcEnergy(int xpos,int ypos,int cpixl);
  void seamTrace(int pos);

  void calcEnergy(); //calculates energy into pixls array
  void seamTrace(); //trace from min seam upwards, mark
                    //index -1 for rebuildimg

  void rebuildImg(); //rebuild pixl array by removing index=-1
                     //marked pixls
  void outputPixl(const char* ofile); //output img currently in pixl array

  void rotateImg(); //do transpose of pixl matrix

  CImg<double> m_inputimg; //main input cimg

  int m_height;
  int m_width;

  pixl** m_pixls;
  pixl** m_pixls2;

  pixl* t_epixls[4]; //energy pixls

  int m_minSeam; //current min seam index
};

#endif