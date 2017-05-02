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

  seam(char* inputfile);

  void calcEnergy(int xpos,int ypos,int cpixl);

  void outputgrey();

 private:
  CImg<double> m_inputimg;

  int m_height;
  int m_width;

  pixl** m_pixls;

  pixl* t_epixls[4]; //energy pixls

  double m_maxEnergy;
};

#endif