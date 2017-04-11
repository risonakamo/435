/*sVtex.c - vertex object
  khang ngo
  cmsc 435 proj4
  represents a vertex.  Stores position data, and things relevant to it
  being transformed during smoothing.  It has an s in the from because 
  every other object we've used so far has an s at the front, i don't know why.*/

#include "sVtex.h"

//constructor takes in slvector3 by reference
sVtex::sVtex(SlVector3 &pt)
:m_pt(&pt),m_plac(0,0,0),m_m(0)
{

}

//umbrella math
void sVtex::umbrella(sVtex &v1,sVtex &v2)
{
  m_plac+=((*(v1.m_pt))-(*m_pt))+((*(v2.m_pt))-(*m_pt));
  m_m+=2;
}

//update position with plac and m
void sVtex::update(float lamb,float dt)
{
  if (m_m==0)
    {
      return;
    }
  
  for (int x=0;x<3;x++)
    {
      m_plac[x]/=m_m;
      (*m_pt)[x]+=(lamb*dt)*m_plac[x];
    }
}

//reset plac and m
void sVtex::reset()
{
  for (int x=0;x<3;x++)
    {
      m_plac[x]=0;
    }

  m_m=0;
}

//debug
void sVtex::printP()
{
  printf("pt %f %f %f pl %f %f %f m %f\n",(*m_pt)[0],(*m_pt)[1],(*m_pt)[2],
         m_plac[0],m_plac[1],m_plac[2],m_m);
}