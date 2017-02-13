//rayd2 ray data 2 because 1 didnt work out so well
#ifndef rayd2_h
#define rayd2_h

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayp.h"

using namespace std;

class rayd2
{
 public:
  rayd2();
  rayd2(float* from,float* at,float* up,int angle,int dim);
  rayd2(rayp* raypars);
  
  void calcVec(); //calculate vectors and other things too
  void genPpoints(); //generate pixel points
  
  void printPars();
  void printPpoints();
  
  /* void loadCircles(float** cdata,int size); */
  void loadCircles(flink2<float*>* cdata);
  void iSphere(); //intersect with stuff
  
 private:
  float rSphere(SlVector3 ray,float* sOrigin); //intRsect sphere
  
  //given values
  SlVector3 m_from;
  SlVector3 m_at;
  SlVector3 m_up;
  int m_angle;
  int m_dim;

  //calculated values
  int m_psize; //pixel grid size
  SlVector3 m_w;
  SlVector3 m_u;
  SlVector3 m_v;
  float m_d;
  float m_m;

  SlVector3* m_ppointsV; //pixel points vector
                         //size should be psize

  int m_csize;
  float** m_cdata; //circle data [x,y,z,r] arrays

  flink2<float*>* m_cdata2;
  flink2<float**>* m_pdata;
};

#endif
