#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "rayd.h"
#include "pogn.h"
#include "../common/slVector.H"

using namespace std;

float rSphere(SlVector3 ray,SlVector3 from,SlVector3 sOrigin,float r);
float rSphere(SlVector3 ray,SlVector3 from,float* sOrigin,float r);

int main()
{
  /* rayd* bob=new rayd; */

  /* bob->argParse("b"); */
  /* bob->argParse("1"); */
  /* bob->argParse(".132"); */
  /* bob->argParse("3"); */

  /* bob->argParse("angle"); */
  /* bob->argParse("32"); */

  /* bob->argParse("resolution"); */
  /* bob->argParse("512"); */
  /* bob->argParse("50000.2"); */

  /* bob->printd(); */

  /* pogn* succ=new pogn("3"); */
  /* succ->load(-123.5); */
  /* succ->load("-.012924302"); */
  /* succ->vprint(); */

  /* printf("\n"); */
  /* SlVector3* bill=new SlVector3(1,2,3); */
  /* cout<<(*bill)<<endl; */

  /* normalize(*bill); */
  /* cout<<*bill<<endl; */

  SlVector3 from(1,0,0);
  SlVector3 at(0,0,0);
  SlVector3 up(0,0,1);
  int angle=90;
  int dim=3; //number of side pixels
  int psize=pow(dim,2);
  
  SlVector3 w=from-at;
  SlVector3 u=cross(up,w);
  SlVector3 v=cross(w,u);

  float d=mag(from-at);
  float m=tan(angle*(3.14/180)*.5)*d;
  
  normalize(w);
  normalize(u);
  normalize(v);
  
  cout<<"w:"<<w<<endl;
  cout<<"u:"<<u<<endl;
  cout<<"v:"<<v<<endl;
  cout<<endl;
  
  cout<<"d:"<<d<<endl;
  cout<<"m:"<<m<<endl;
  cout<<endl;
  
  float* r;
  float* ppoints[psize];
  SlVector3 ppointsV[psize];
  int x=0;
  int y=0;

  for (int z=0;z<psize;z++)
    {
      r=new float[2];
      r[0]=-m+(x*((2*m)/dim))+(m/dim);
      r[1]=-m+(y*((2*m)/dim))+(m/dim);

      x++;
      if (x>=dim)
        {
          x=0;
          y++;
        }

      /* ppoints[z]=r; */
      /* cout<<r[0]<<" "<<r[1]<<endl; */
      
      ppointsV[z]=(r[0]*u)-(r[1]*v)-(d*w);
    }

  /* cout<<(ppoints[4][0]*u)-(ppoints[4][1]*v)-(d*w)<<endl; */

  rSphere(ppointsV[4],from,SlVector3(-2,0,0),1);
  
  return 0;
}

float rSphere(SlVector3 ray,SlVector3 from,SlVector3 sOrigin,float r)
{
  float sOriginF[3]; //sphere origin float
  for (int x=0;x<3;x++)
    {
      sOriginF[x]=sOrigin[x];
    }

  return rSphere(ray,from,sOriginF,r);
}

float rSphere(SlVector3 ray,SlVector3 from,float* sOrigin,float r)
{
  SlVector3 iPoint=ray+from;

  float a=0;
  float b=0;
  float c1=0;
  float c2=0;
  float c3=0;
  for (int x=0;x<3;x++)
    {
      a+=pow(ray[x],2);
      b+=ray[x]*(from[x]-sOrigin[x]);
      c1+=pow(sOrigin[x],2);
      c2+=pow(from[x],2);
      c3+=sOrigin[x]*from[x];
    }

  b*=2;
  c1=c1+c2+(-2*c3-pow(r,2));

  float dis=pow(b,2)-(4*a*c1);
  
  cout<<"rsphere:"<<dis<<endl;
  return 0;
}
