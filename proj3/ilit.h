/*ilit.h - intersection object
 khang ngo
 cmsc 435 proj2
 represents different types of objects used in intersecting,
 including spheres polygons and lights. stores data as 1d array
 and doubles as linked list*/

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
