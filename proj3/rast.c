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
  printf("%f %f %f\n",m_adata->m_data[0],m_adata->m_data[1],m_adata->m_data[2]);
}


