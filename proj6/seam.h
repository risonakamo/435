/*seam.h - main seam object
  khang ngo
  cmsc 435 proj 6
  main seam object.  loads image and does energy calculation,
  seam tracing, and image output. stores image as array of
  pixl objects*/

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

  void resize(int width,int height,const char* ofile); //run main resize function

  /*-- debug --*/
  void printEnergy(); //print all energies

 private:
 /*-- main loop functions --*/
  void calcEnergy(); //calculates energy into pixls array
  void calcEnergy(int xpos,int ypos,int cpixl); //energy helper

  void seamTrace(); //trace from min seam upwards, mark
                    //index -1 for rebuildimg
  void seamTrace(int pos);

  void rebuildImg(); //rebuild pixl array by removing index=-1
                     //marked pixls
  void outputPixl(const char* ofile); //output img currently in pixl array

  void rotateImg(); //do transpose of pixl matrix

  /*-- member vars --*/
  CImg<double> m_inputimg; //main input cimg

  int m_height; //current pixl array dimensions
  int m_width;

  pixl** m_pixls; //pixl arrays
  pixl** m_pixls2;

  pixl* t_epixls[4]; //energy pixls

  int m_minSeam; //current min seam index
};

#endif