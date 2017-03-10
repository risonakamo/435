/*rayp.h - ray parser
  khang ngo
  cmsc 435 proj 2
  includes rayp object and flink2.  rayp object handles
  nff file parsing to be passed onto the rayd which does
  the math work*/

#ifndef rayp_h
#define rayp_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "iobj.h"

using namespace std;

class rayp
{
 public:
  rayp();
  
  void loadFile(string filename);
  void loadFile(string filename,string ofile);
  
  void argParse(string a); //parse an arg

  void printd(); //print relevant data stored
  void printad(); //print all data debug only

  /*--public vars--*/
  //various math-related data terms
  double m_from[3];
  double m_at[3];
  double m_up[3];
  int m_angle;
  int m_res[2];
  
  double m_background[3]; 
  int m_hither;
  double* m_fill;

  string m_ofile; //name of output file

  /*--data stuff--*/
  iobj* m_adata; /*any data, uses new iobj, holds float array able to represent
                   both spheres and polygons, dont have to be seperate*/
  iobj* m_light; //light objs have to be seperate though
  int m_maxLight; //number of lights
  
 private:
  /*--private functions--*/
  void arrayParse(int mmode,string a); //parse array like data
  int arrayParseFill(int mmode,string a); //helper
  void cparse(string &a); //parse spheres
  void pparse(string &a,int dims); //parse polygons
  int lparse(string &a); //parse lights

  void fanTriangle(int dim); //split polygon to triangles

  int checkDouble(string &a); //check if input was double
  
  /*--mode:--
    0=no mode
    1=background
    2=from
    3=at
    4=up
    5=angle
    6=hither
    7=resolution
    8=l light
    9=f for fill
    10=p for polygon
    11=s for circle
    12=pp polygon patch
  */
  int m_mode;
  int m_mc; //mode count
  
  /*--circle temps--*/
  double* m_tc; //tc temp circle

  /*--polygon temps--*/
  int m_pc; //max point count of current polygon
  double** m_tpg; //temp polygon
  double** m_tpg2; //temp polygon 2
  double* m_tp; //tp temp point
  int m_pctr; //point counter
  int m_pctr2; //point counter2
};

#endif
