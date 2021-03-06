/*iobj.h - intersection object
 khang ngo
 cmsc 435 proj2
 represents different types of objects used in intersecting,
 including spheres polygons and lights. stores data as 1d array
 and doubles as linked list*/

#ifndef iobj_h
#define iobj_h

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class iobj
{
 public:
  iobj();

  iobj(int type,double* data,double* colour,iobj* next);

  //debug print
  void print();
  
  /*type of shape thing:
   0=undefined
   1=sphere
   2=triangle
   3=patch
   4=light*/
  int m_type;
  double* m_data; //double array of data
  double* m_colour; /*colour array, potentially a shared pointer
                      with other objs with same coloured*/
  iobj* m_next; //link to next object

 private:
  
};

#endif
