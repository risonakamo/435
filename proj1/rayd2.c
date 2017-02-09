#include "rayd2.h"

using namespace std;

rayd2::rayd2()
:m_from(0,0,0),m_at(0,0,0),m_up(0,0,0),m_angle(0),m_dim(0)
{

}

rayd2::rayd2(float* from,float* at,float* up,int angle,int dim)
:m_angle(angle),m_dim(dim)
{
  for (int x=0;x<3;x++)
    {
      m_from[x]=from[x];
      m_at[x]=at[x];
      m_up[x]=up[x];      
    }
}

void rayd2::calcVec()
{
  if (m_dim==0)
    {
      cout<<"rayd2 calcvec: not all variables set"<<endl;
      return;
    }

  m_psize=pow(m_dim,2);
  
  m_w=m_from-m_at;
  m_u=cross(m_up,m_w);
  m_v=cross(m_w,m_u);

  m_d=mag(m_from-m_at);
  m_m=tan(m_angle*(M_PI/180)*.5)*m_d;

  normalize(m_w);
  normalize(m_u);
  normalize(m_v);
}

void rayd2::genPpoints()
{  
  m_ppointsV=new SlVector3[m_psize];

  float r[2]; //temp vars random letters
  int x=0;
  int y=0;

  for (int z=0;z<m_psize;z++)
    {
      r[0]=-m_m+(x*((2*m_m)/m_dim))+(m_m/m_dim);
      r[1]=-m_m+(y*((2*m_m)/m_dim))+(m_m/m_dim);

      x++;
      if (x>=m_dim)
        {
          x=0;
          y++;
        }

      m_ppointsV[z]=(r[0]*m_u)-(r[1]*m_v)-(m_d*m_w);
    }
}

void rayd2::printPars()
{
  cout<<"from:"<<m_from<<endl;
  cout<<"at:"<<m_at<<endl;
  cout<<"up:"<<m_up<<endl;
  cout<<endl;
  
  cout<<"angle:"<<m_angle<<endl;
  cout<<"dim:"<<m_dim<<endl;
  cout<<endl;
  
  cout<<"w:"<<m_w<<endl;
  cout<<"u:"<<m_u<<endl;
  cout<<"v:"<<m_v<<endl;
  cout<<endl;
  
  cout<<"d:"<<m_d<<endl;
  cout<<"m:"<<m_m<<endl;
  cout<<endl;
}

void rayd2::loadCircles(float** cdata)
{
  m_cdata=cdata;
}

void rayd2::printPpoints()
{
  for (int x=0;x<m_psize;x++)
    {
      cout<<m_ppointsV[x]<<endl;      
    }

  cout<<endl;
}
