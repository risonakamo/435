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

  void calcEnergy(int grey); //calculates energy into pixls array, put grey=1
                             //to skip adding min parents
  void seamTrace();

  void rebuildImg();
  void outputPixl();

  /*-- debug --*/
  void printEnergy(); //print all energies
  void outputgrey(); //output grey img

 private:
 /*-- helper functions --*/
  void calcEnergy(int xpos,int ypos,int cpixl,int grey);
  void seamTrace(int pos);

  CImg<double> m_inputimg; //main input cimg

  int m_height;
  int m_width;

  pixl** m_pixls;
  pixl** m_pixls2;

  pixl* t_epixls[4]; //energy pixls

  double m_maxEnergy; //current max energy (for grey)
  int m_minSeam; //current min seam index
};

#endif