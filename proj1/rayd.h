#ifndef rayd_h
#define rayd_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//rayd for ray data
class rayd
{
 public:
  rayd();

  void argParse(string a);

  void printd();
  
 private:
  void arrayParse(int mmode,string a);
  int arrayParseFill(int mmode,string a);
  
  /*mode:
    0=no mode
    1=background
    2=from
    3=at
    4=up
    5=angle
    6=hither
    7=resolution
    8=l
    9=f for fill
    10=p for polygon
  */
  int m_mode;
  int m_mc; //mode count
  
  float m_background[3];
  
  float m_from[3];
  float m_at[3];
  float m_up[3];
  int m_angle;
  int m_hither;
  int m_res[2];
  float m_fill[8];
};

#endif
