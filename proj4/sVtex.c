#include "sVtex.h"

sVtex::sVtex(SlVector3 &pt)
:m_pt(&pt),m_plac(0,0,0),m_m(0)
{

}

void sVtex::umbrella(sVtex &v1,sVtex &v2)
{
  // cout<<m_plac<<"+("<<*(v1.m_pt)<<"-"<<(*m_pt)<<")+("<<*(v2.m_pt)<<"-"<<(*m_pt)<<")"<<"=";

  m_plac+=((*(v1.m_pt))-(*m_pt))+((*(v2.m_pt))-(*m_pt));

  m_m+=2;

  // cout<<m_plac<<" m="<<m_m<<endl;
}

void sVtex::update(float lamb,float dt)
{
  if (m_m==0)
    {
      return;
    }
  
  for (int x=0;x<3;x++)
    {
      // cout<<m_plac<<" m="<<m_m<<endl;
      m_plac[x]/=m_m;
      (*m_pt)[x]+=(lamb*dt)*m_plac[x];
    }
}

void sVtex::reset()
{
  for (int x=0;x<3;x++)
    {
      m_plac[x]=0;
    }

  m_m=0;
}

void sVtex::printP()
{
  printf("pt %f %f %f pl %f %f %f m %f\n",(*m_pt)[0],(*m_pt)[1],(*m_pt)[2],
         m_plac[0],m_plac[1],m_plac[2],m_m);
}