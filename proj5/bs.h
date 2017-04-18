//bs boid system

#ifndef BS_H
#define BS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../common/slVector.H"

using namespace std;

class bs
{
 public:
  bs();
  bs(const string filename);
  
  void loadFile(const string filename);

  void parseBoid(string bstring);
  
  void printPars();
  void printVecs();
  
 private:
  float m_pars[12];

  vector<SlVector3> m_points;
  vector<SlVector3> m_vels;

  int t_bmode;
};

#endif
