/*rayp.h - ray parser
  khang ngo
  cmsc 435 proj 1
  includes rayp object and flink2.  rayp object handles
  nff file parsing to be passed onto the rayd which does
  the math work*/

#ifndef rayp_h
#define rayp_h

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//float link 2, now with templates
//its just a linked list
template <class T>
class flink2
{
 public:
  flink2();

  flink2(T data);

  T m_data;
  flink2<T>* m_next;
};

template <class T>
flink2<T>::flink2()
:m_next(NULL)
{

}

template <class T>
flink2<T>::flink2(T data)
:m_data(data),m_next(NULL)
{

}

class rayp
{
 public:
  rayp();
  
  void loadFile(string filename);
  void loadFile(string filename,string ofile);
  
  void argParse(string a); //parse an arg

  void printd(); //print relevant data stored
  void printc(); //print circles
  void printt(); //print triangles

  /*--public vars--*/
  //various math-related data terms
  float m_from[3];
  float m_at[3];
  float m_up[3];
  int m_angle;
  int m_res[2];

  float m_background[3]; 
  int m_hither;
  float m_fill[8];

  string m_ofile;

  /*--data stuff--*/
  flink2<float*>* m_cdata; //circle data
  flink2<float**>* m_pdata; //polygon data
  
 private:
  void arrayParse(int mmode,string a); //parse array like data
  int arrayParseFill(int mmode,string a); //helper
  void cparse(string &a); //parse spheres
  void pparse(string &a); //parse polygons
  
  /*mode:
    0=no mode
    1=background
    2=from
    3=at
    4=up
    5=angle
    6=hither
    7=resolution
    8=l
    9=f for fill
    10=p for polygon
    11=s for circle
  */
  int m_mode;
  int m_mc; //mode count
  
  /*--circle temps--*/
  float* m_tc; //tc temp circle

  /*--polygon temps--*/
  int m_pc; //max point count of current polygon
  float** m_tpg; //temp polygon
  float** m_tpg2; //temp polygon 2
  float* m_tp; //tp temp point
  int m_pctr; //point counter
  int m_pctr2; //point counter2
};

#endif
