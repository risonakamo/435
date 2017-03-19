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

  iobj(int type,double* data,double* tdata,double* colour,iobj* next);
  
  //debug print
  void print();

  //print 4d transformed points x3 (NOT A MATRIX!!!)
  void printTdata();

  void printVcolour();

  void splitN();
  
  /*type of shape thing:
   0=undefined
   1=sphere
   2=triangle
   3=patch
   4=light*/
  int m_type;
  double* m_data; //double array of data
  double* m_tdata; //transform data
  double*
    m_ndata; //normal data
  double m_zDep[3]; //closest zdepth of triangle
  double* m_colour; /*colour array, potentially a shared pointer
                      with other objs with same coloured*/
  double m_vcolour[9];
  iobj* m_next; //link to next object

 private:
};

#endif
