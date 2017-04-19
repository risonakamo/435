//bs boid system

#ifndef BS_H
#define BS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

#include "../common/slVector.H"
#include "kdTree.H"

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
  void treeTest();
  
 private:
  /*-- initialise --*/
  void calc();
  void parseBoid(string bstring);

  /*-- run stuff --*/
  void boundCheck(SlVector3 &point,SlVector3 &vel);
  void centreForce(SlVector3 &point,vector<int> &nbours,int &iself);
  void matchVel(SlVector3 &point,vector<int> &nbours,int &iself);
  void colliForce(SlVector3 &point,vector<int> &nbours,int &iself);
  
  /*-- output --*/
  void boutput();

  /*-- important stuff --*/
  FILE* m_f;
  float m_pars[12];
  KDTree* m_tree;

  int m_numBirds;
  int m_maxNbour;
  int m_frames;
  vector<SlVector3> m_points;
  vector<SlVector3> m_vels;

  /*-- temps --*/
  int t_bmode; //parseboid temp

  SlVector3 t_force;
  SlVector3 t_vec;
};

#endif
