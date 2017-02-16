#include <string>
#include <iostream>
#include <cmath>

#include "../common/slVector.H"

using namespace std;

int main()
{
  float from[3]={0,0,0};
  float ray[3]={1,0,0};
  /* float p[9]={2,0,1, */
  /*             2,1,-1, */
  /*             2,-1,-1}; */

  float p[9]={0,1,1,
              1,.00000001,-1,
              -1,1,-1};


  float r[12]={p[0]-p[3],p[0]-p[6],ray[0],p[0]-from[0],
               p[1]-p[4],p[1]-p[7],ray[1],p[1]-from[1],
               p[2]-p[5],p[2]-p[8],ray[2],p[2]-from[2]};

  float s[6]={(r[5]*r[10])-(r[6]*-r[9]),
              (r[2]*r[9])-(r[1]*r[10]),
              (r[1]*r[6])-(r[5]*r[2]),
              (r[0]*r[7])-(r[3]*r[4]),
              (r[3]*r[8])-(r[0]*r[11]),
              (r[4]*r[11])-(r[7]*r[8])};
  
  float m=(r[0]*s[0])+(r[4]*s[1])+(r[8]*s[2]);
  float b=((r[3]*s[0])+(r[7]*s[1])+(r[11]*s[2]))/m;
  float a=((r[10]*s[3])+(r[6]*s[4])+(r[2]*s[5]))/m;
  float t=((r[9]*s[3])+(r[5]*s[4])+(r[1]*s[5]))/m;

  cout<<"m: "<<m<<endl;
  cout<<"t: "<<t<<endl;
  cout<<"b: "<<b<<endl;
  cout<<"a: "<<a<<endl;

  
  return 0;
}

int rTri2(float* ray,float* from,float* p)
{
  //matrix A
  float r[12]={p[0]-p[3],p[0]-p[6],ray[0],p[0]-from[0],
               p[1]-p[4],p[1]-p[7],ray[1],p[1]-from[1],
               p[2]-p[5],p[2]-p[8],ray[2],p[2]-from[2]};

  //pre-do subtractions
  float s[6]={(r[5]*r[10])-(r[6]*-r[9]),
              (r[2]*r[9])-(r[1]*r[10]),
              (r[1]*r[6])-(r[5]*r[2]),
              (r[0]*r[7])-(r[3]*r[4]),
              (r[3]*r[8])-(r[0]*r[11]),
              (r[4]*r[11])-(r[7]*r[8])};

  float x;
  //determinant
  x=(r[0]*s[0])+(r[4]*s[1])+(r[8]*s[2]);

  if (x==0)
    {
      return 0;
    }

  //a (alpha or whatever greek a is, textbook uses r)
  float a=((r[10]*s[3])+(r[6]*s[4])+(r[2]*s[5]))/m;

  if (x<0 || x>1)
    {
      return 0;
    }

  //B (beta or whatever capital greek b is)
  x=((r[3]*s[0])+(r[7]*s[1])+(r[11]*s[2]))/m;

  if (x<0 || x>1-a)
    {
      return 0;
    }
  
  return 1;
}
