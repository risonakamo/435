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

  void print();
  
  /*type of shape thing:
   0=undefined
   1=sphere
   2=triangle
   3=patch
   4=light*/
  int m_type;
  double* m_data;
  double* m_colour;
  iobj* m_next;

 private:
  
};

#endif
