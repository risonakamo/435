#include "sVtex.h"

sVtex::sVtex(SlVector3 &pt)
:m_pt(&pt),m_plac(0,0,0),m_m(0)
{

}

void sVtex::umbrella(sVtex &v1,sVtex &v2)
{
  m_plac+=((*(v1.m_pt))-(*m_pt))+((*(v2.m_pt))-(*m_pt));
  m_m+=2;
}

void sVtex::update(float lamb,float dt)
{
  if (m_m==0)
    {
      return;
    }
  
  for (int x=0;x<3;x++)
    {
      (*m_pt)[x]+=(lamb*dt)*(m_plac[x]/m_m);
    }
}

void sVtex::printP()
{
  printf("%f %f %f %f %f %f %f\n",(*m_pt)[0],(*m_pt)[1],(*m_pt)[2],
         m_plac[0],m_plac[1],m_plac[2],m_m);
}
