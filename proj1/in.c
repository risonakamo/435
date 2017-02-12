#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "../common/slVector.H"
#include "rayd2.h"
#include "rayp.h"

using namespace std;

float rSphere(SlVector3 ray,SlVector3 from,SlVector3 sOrigin,float r);
float rSphere(SlVector3 ray,SlVector3 from,float* sOrigin,float r);
float rTri(SlVector3 &ray,SlVector3 &from,float* p1,float* p2,float* p3);
float rTri(SlVector3 &ray,SlVector3 &from,SlVector3 p1,SlVector3 p2,SlVector3 p3);

int main()
{
  /* rayp* bill=new rayp; */
  /* bill->loadFile("a.nff"); */

  /* rayd2 bob(bill); */
  /* bob.calcVec(); */
  /* bob.genPpoints(); */
  /* bob.printPars(); */
  /* bob.iSphere(); */

  float p1[3]={2,0,1};
  float p2[3]={2,1,-1};
  float p3[3]={2,-1,-1};

  float p4[3]={0,1,1};
  float p5[3]={1,1,-1};
  float p6[3]={-1,1,-1};

  float p7[3]={-2,0,1};
  float p8[3]={-2,1,-1};
  float p9[3]={-2,-1,-1};

  float p10[3]={-2,0,1};
  float p11[3]={0,-1,0};
  float p12[3]={-3,0,-1};
  
  SlVector3 r(1,0,0);
  SlVector3 from(0,0,0);

  cout<<rTri(r,from,p1,p2,p3)<<endl;
  cout<<rTri(r,from,p4,p5,p6)<<endl;
  cout<<rTri(r,from,p7,p8,p9)<<endl;
  cout<<rTri(r,from,p10,p11,p12)<<endl;
  
  return 0;
}

float rTri(SlVector3 &ray,SlVector3 &from,float* p1,float* p2,float* p3)
{
  SlVector3 pv1;
  SlVector3 pv2;
  SlVector3 pv3;

  for (int x=0;x<3;x++)
    {
      pv1[x]=p1[x];
      pv2[x]=p2[x];
      pv3[x]=p3[x];
    }

  return rTri(ray,from,pv1,pv2,pv3);
}

float rTri(SlVector3 &ray,SlVector3 &from,SlVector3 p1,SlVector3 p2,SlVector3 p3)
{
  SlVector3 edge1=p2-p1;
  SlVector3 edge2=p3-p1;
  
  SlVector3 a=cross(ray,edge2);
  float d=dot(edge1,a);

  if (d==0)
    {
      return 0;
    }

  cout<<"d:"<<d<<endl;
  SlVector3 b=from-p1;
  float b1=dot(b,a)/d;

  cout<<"b1:"<<b1<<endl;
  if (b1<0.0 || b1>1.0)
    {
      return 0;
    }

  SlVector3 c=cross(b,edge1);
  float c1=dot(ray,c)/d;

  cout<<"c1:"<<c1<<endl;
  if (c1<0.0 || b1+c1>1.0)
    {
      return 0;
    }

  if ((dot(edge2,c)/d)>0.0)
    {
      return 1;
    }

  return 0;
}

//rsphere with size 4 array for sphere (x,y,z,r)
//where x y z is centre coordinate
float rSphere(SlVector3 ray,SlVector3 from,float* sOrigin)
{
  return rSphere(ray,from,sOrigin,sOrigin[3]);
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

int oldtestmain()
{
  /* SlVector3 from(1,0,0); */
  /* SlVector3 at(0,0,0); */
  /* SlVector3 up(0,0,1); */
  /* int angle=90; */
  /* int dim=3; //number of side pixels */
  /* int psize=pow(dim,2); */
  
  /* SlVector3 w=from-at; */
  /* SlVector3 u=cross(up,w); */
  /* SlVector3 v=cross(w,u); */

  /* float d=mag(from-at); */
  /* float m=tan(angle*(M_PI/180)*.5)*d; */
  
  /* normalize(w); */
  /* normalize(u); */
  /* normalize(v); */
  
  /* cout<<"w:"<<w<<endl; */
  /* cout<<"u:"<<u<<endl; */
  /* cout<<"v:"<<v<<endl; */
  /* cout<<endl; */
  
  /* cout<<"d:"<<d<<endl; */
  /* cout<<"m:"<<m<<endl; */
  /* cout<<endl; */
  
  /* float r[2]; */
  /* SlVector3* ppointsV=new SlVector3[psize]; */
  /* int x=0; */
  /* int y=0; */

  /* for (int z=0;z<psize;z++) */
  /*   { */
  /*     r[0]=-m+(x*((2*m)/dim))+(m/dim); */
  /*     r[1]=-m+(y*((2*m)/dim))+(m/dim); */

  /*     x++; */
  /*     if (x>=dim) */
  /*       { */
  /*         x=0; */
  /*         y++; */
  /*       } */

  /*     /\* ppoints[z]=r; *\/ */
  /*     /\* cout<<r[0]<<" "<<r[1]<<endl; *\/ */
      
  /*     ppointsV[z]=(r[0]*u)-(r[1]*v)-(d*w); */
  /*     cout<<ppointsV[z]<<endl; */
  /*   } */

  /* /\* cout<<(ppoints[4][0]*u)-(ppoints[4][1]*v)-(d*w)<<endl; *\/ */

  /* rSphere(ppointsV[4],from,SlVector3(-2,0,0),1);   */

  //other old main
  /* float rfrom[3]={1,0,0}; */
  /* float rat[3]={0,0,0}; */
  /* float rup[3]={0,0,1}; */
  /* int rangle=90; */
  /* int rdim=100; */

  /* float* cdata[1]; */
  /* float c[4]={-2,0,0,20}; */
  /* cdata[0]=c; */
  
  /* rayd2 bob(rfrom,rat,rup,rangle,rdim); */
  /* bob.calcVec(); */
  /* bob.genPpoints(); */
  /* bob.printPars(); */

  /* bob.loadCircles(cdata,1); */
  /* bob.iSphere(); */
}
