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

  void calcEnergy(); //calculates energy into pixls array, put grey=1
                             //to skip adding min parents
  void seamTrace(); //trace from min seam upwards, mark
                    //index -1 for rebuildimg

  void rebuildImg(); //rebuild pixl array by removing index=-1
                     //marked pixls
  void outputPixl(); //output img currently in pixl array

  void rotateImg(); //do transpose of pixl matrix

  void resize(int width,int height);

  /*-- debug --*/
  void printEnergy(); //print all energies

 private:
 /*-- helper functions --*/
  void calcEnergy(int xpos,int ypos,int cpixl);
  void seamTrace(int pos);

  CImg<double> m_inputimg; //main input cimg

  int m_height;
  int m_width;

  pixl** m_pixls;
  pixl** m_pixls2;

  pixl* t_epixls[4]; //energy pixls

  int m_minSeam; //current min seam index
};

#endif