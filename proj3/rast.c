#include "rast.h"

rast::rast()
:m_from(0,0,0),m_at(0,0,0),m_up(0,0,0),m_angle(0),m_dim(0),
  m_ofile("output.ppm"),m_adata(NULL)
{

}

rast::rast(rayp* raypars)
:m_angle(raypars->m_angle),m_dim(raypars->m_res[0]),
  m_ofile(raypars->m_ofile),m_adata(raypars->m_adata),
  m_light(raypars->m_light),m_maxLight(raypars->m_maxLight),
  m_hither(raypars->m_hither)
{
  for (int x=0;x<3;x++)
    {
      m_from[x]=raypars->m_from[x];
      m_at[x]=raypars->m_at[x];
      m_up[x]=raypars->m_up[x];
      m_background[x]=raypars->m_background[x]*255;
      m_backgroundF[x]=raypars->m_background[x];
    }
}

void rast::calcVec()
{
  //lazy check only meant for if default constructor
  //was called
  if (m_dim==0)
    {
      cout<<"rayd2 calcvec: not all variables set"<<endl;
      return;
    }

  //pixel grid size, supports only squares right now
  m_psize=pow(m_dim,2);

  //camera point u v w thing
  m_w=m_from-m_at;
  m_u=cross(m_up,m_w);
  m_v=cross(m_w,m_u);

  //fov and pixel grid distance from camera
  m_d=m_hither;
  /* m_m=tan(m_angle*(M_PI/180)*.5)*m_d; */

  normalize(m_w);
  normalize(m_u);
  normalize(m_v);

  Mcam(m_adata);
}

void rast::Mcam(iobj* tri)
{
  if (tri->m_type!=2 && tri->m_type!=3)
    {
      return;
    }

  float fromSub[12];
  tri->m_tdata[3]=1;
  tri->m_tdata[7]=1;
  tri->m_tdata[11]=1;  
  
  for (int x=0;x<3;x++)
    {
      fromSub[x]=tri->m_data[x]-m_from[x];
      fromSub[x+3]=tri->m_data[x+3]-m_from[x];
      fromSub[x+6]=tri->m_data[x+6]-m_from[x];
    }

  tri->m_tdata[0]=(m_u[0]*fromSub[0])+(m_u[1]*fromSub[1])+(m_u[2]*fromSub[2]);
  tri->m_tdata[1]=(m_v[0]*fromSub[0])+(m_v[1]*fromSub[1])+(m_v[2]*fromSub[2]);
  tri->m_tdata[2]=(m_w[0]*fromSub[0])+(m_w[1]*fromSub[1])+(m_w[2]*fromSub[2]);

  tri->m_tdata[4]=(m_u[0]*fromSub[4])+(m_u[1]*fromSub[5])+(m_u[2]*fromSub[6]);
  tri->m_tdata[5]=(m_v[0]*fromSub[4])+(m_v[1]*fromSub[5])+(m_v[2]*fromSub[6]);
  tri->m_tdata[6]=(m_w[0]*fromSub[4])+(m_w[1]*fromSub[6])+(m_w[2]*fromSub[6]);

  tri->m_tdata[8]=(m_u[0]*fromSub[8])+(m_u[1]*fromSub[9])+(m_u[2]*fromSub[10]);
  tri->m_tdata[9]=(m_v[0]*fromSub[8])+(m_v[1]*fromSub[9])+(m_v[2]*fromSub[10]);
  tri->m_tdata[10]=(m_w[0]*fromSub[8])+(m_w[1]*fromSub[9])+(m_w[2]*fromSub[10]);

  tri->print();
  tri->printTdata();
}
