#ifndef pogn_h
#define pogn_h

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class pogn
{
 public:
  pogn();

  pogn(int v);
  pogn(string v);

  ~pogn();
  
  void load(float p);
  void load(string p);

  void vprint();
  
 private:
  void _load(float p);
  
  int m_ms; //ms for max size
  int m_p; //p for pos
  float* m_d; //d for data
};

#endif
