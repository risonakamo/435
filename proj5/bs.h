/*bs.h - boid system
  khang ngo
  cmsc 435 proj 5
  takes in input file and performs calculation of boid movements
  using a variety of forces.*/

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
  //if using the 2nd constructor, calls this immediately
  void loadFile(const string filename,const string outfile);
  
  /*-- run --*/
  void run(); //main program loop

  /*-- debug --*/
  void printPars();
  void printVecs();
  void treeTest();
  
 private:
  /*-- initialise --*/
  void parseBoid(string bstring);
  void parseFood(string &fstring);

  /*-- run stuff --*/
  void centreForce(SlVector3 &point,vector<int> &nbours,int &iself);
  void matchVel(SlVector3 &point,vector<int> &nbours,int &iself);
  void colliForce(SlVector3 &point,vector<int> &nbours,int &iself);
  void foodForce(SlVector3 &point);

  void boundCheck(SlVector3 &point,SlVector3 &vel); //check out of bounds
  void foodSnap(SlVector3 &food); //move food in bounds

  /*-- output --*/
  void boutput();

  /*-- important stuff --*/
  FILE* m_f;
  float m_pars[12];  //input vars
  KDTree* m_tree;
  KDTree* m_ftree;

  //int input vars/calculated values
  int m_numBirds;
  int m_maxNbour;
  int m_frames;
  int m_numFood;
  int m_currFood;

  //points and velocities
  vector<SlVector3> m_points;
  vector<SlVector3> m_vels;

  //food data
  vector<SlVector3> m_foods;
  vector<SlVector3> m_foodVel;
  vector<int> m_foodT;

  /*-- temps --*/
  int t_bmode; //parseboid temp
  int t_fmode; //parsefood temp

  //used in force calculations
  SlVector3 t_force;
  SlVector3 t_vec;
};

#endif
