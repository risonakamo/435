/*ilit.c - intersection light rasteriser version
 khang ngo
 cmsc 435 proj3
 simplified version of the iobj. was seperated
 when the iobj got a lot more data members than a
 light would ever need, so they couldnt share data
 types anymore*/

#ifndef ilit_h
#define ilit_h

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class ilit
{
 public:
  ilit();

  ilit(double* data,double* colour,ilit* next); 
  
  /*type of shape thing:
   4=light*/
  int m_type;
  double* m_data; //double array of data
  double* m_colour; //colour array
  ilit* m_next; //link to next object

 private:
  
};

#endif
