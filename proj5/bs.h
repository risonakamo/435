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
  bs(const string filename,const string outfile);
  
  /*-- initialise stuff --*/
  void loadFile(const string filename,const string outfile);
  
  /*-- run --*/
  void run();

  /*-- debug --*/
  void printPars();
  void printVecs();
  
 private:
  /*-- initialise --*/
  void calc();
  void parseBoid(string bstring);

  /*-- output --*/
  void boutput();

  FILE* m_f;
  float m_pars[12];

  int m_frames;
  vector<SlVector3> m_points;
  vector<SlVector3> m_vels;

  int t_bmode; //parseboid temp
};

#endif
