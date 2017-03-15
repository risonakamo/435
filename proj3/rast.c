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
  m_img=new int[m_psize];

  //camera point u v w thing
  m_w=m_from-m_at;
  m_u=cross(m_up,m_w);
  m_v=cross(m_w,m_u);

  //fov and pixel grid distance from camera
  m_m=tan(m_angle*(M_PI/180)*.5)*m_hither;
  m_d=(2*m_m)/m_dim;

  normalize(m_w);
  normalize(m_u);
  normalize(m_v);

  Mcam(m_adata);
  MP(m_adata);
  MZdiv(m_adata);
  Morth(m_adata);
  Mvp(m_adata);

  m_adata->printTdata();
  boundFill(m_adata);
}

/* void rast::Mcam_old(iobj* tri) */
/* { */
/*   if (tri->m_type!=2 && tri->m_type!=3) */
/*     { */
/*       return; */
/*     } */

/*   float fromSub[12]; */
/*   tri->m_tdata[3]=1; */
/*   tri->m_tdata[7]=1; */
/*   tri->m_tdata[11]=1;   */
  
/*   for (int x=0;x<3;x++) */
/*     { */
/*       fromSub[x]=tri->m_data[x]-m_from[x]; */
/*       fromSub[x+3]=tri->m_data[x+3]-m_from[x]; */
/*       fromSub[x+6]=tri->m_data[x+6]-m_from[x]; */
/*     } */

/*   tri->m_tdata[0]=(m_u[0]*fromSub[0])+(m_u[1]*fromSub[1])+(m_u[2]*fromSub[2]); */
/*   tri->m_tdata[1]=(m_v[0]*fromSub[0])+(m_v[1]*fromSub[1])+(m_v[2]*fromSub[2]); */
/*   tri->m_tdata[2]=(m_w[0]*fromSub[0])+(m_w[1]*fromSub[1])+(m_w[2]*fromSub[2]); */

/*   tri->m_tdata[4]=(m_u[0]*fromSub[4])+(m_u[1]*fromSub[5])+(m_u[2]*fromSub[6]); */
/*   tri->m_tdata[5]=(m_v[0]*fromSub[4])+(m_v[1]*fromSub[5])+(m_v[2]*fromSub[6]); */
/*   tri->m_tdata[6]=(m_w[0]*fromSub[4])+(m_w[1]*fromSub[6])+(m_w[2]*fromSub[6]); */

/*   tri->m_tdata[8]=(m_u[0]*fromSub[8])+(m_u[1]*fromSub[9])+(m_u[2]*fromSub[10]); */
/*   tri->m_tdata[9]=(m_v[0]*fromSub[8])+(m_v[1]*fromSub[9])+(m_v[2]*fromSub[10]); */
/*   tri->m_tdata[10]=(m_w[0]*fromSub[8])+(m_w[1]*fromSub[9])+(m_w[2]*fromSub[10]); */
/* } */

void rast::Mcam(iobj* tri)
{
  int z=0;
  for (int x=0;x<12;x+=4)
    {      
      for (int y=0;y<3;y++)
        {
          m_Mtemp[y]=tri->m_data[z*3+y]-m_from[y];
          tri->m_tdata[x+y]=0;
        }

      z++;
      
      for (int y=0;y<3;y++)
        {
          tri->m_tdata[x]+=m_u[y]*m_Mtemp[y];
          tri->m_tdata[x+1]+=m_v[y]*m_Mtemp[y];
          tri->m_tdata[x+2]+=m_w[y]*m_Mtemp[y];
        }

      tri->m_tdata[x+3]=1;
    }
}

void rast::MP(iobj* tri)
{
  for (int x=0;x<12;x+=4)
    {
      for (int y=0;y<4;y++)
        {
          m_Mtemp[y]=tri->m_tdata[x+y];
        }

      tri->m_tdata[x]=m_hither*m_Mtemp[0];
      tri->m_tdata[x+1]=m_hither*m_Mtemp[1];
      tri->m_tdata[x+2]=(101*m_hither*m_Mtemp[2])+(((-100*m_hither)*m_hither)*m_Mtemp[3]);
      tri->m_tdata[x+3]=m_Mtemp[2];
    }
}

void rast::Morth(iobj* tri)
{
  for (int x=0;x<12;x+=4)
    {
      for (int y=0;y<3;y++)
        {
          m_Mtemp[y]=tri->m_tdata[x+y];
        }

      tri->m_tdata[x]=(1/m_m)*m_Mtemp[0];
      tri->m_tdata[x+1]=(1/m_m)*m_Mtemp[1];
      tri->m_tdata[x+2]=(((2/99*m_hither))*m_Mtemp[2])+((-101/99)*m_Mtemp[3]);
    }
}

void rast::Mvp(iobj* tri)
{   
  for (int x=0;x<12;x+=4)
    {
      for (int y=0;y<2;y++)
        {
          m_Mtemp[y]=tri->m_tdata[x+y];
        }

      tri->m_tdata[x]=((m_dim/2)*m_Mtemp[0])+(((m_dim-1)/2)*m_Mtemp[3]);
      tri->m_tdata[x+1]=((m_dim/2)*m_Mtemp[1])+(((m_dim-1)/2)*m_Mtemp[3]);
    }
}

void rast::MZdiv(iobj* tri)
{
  for (int x=0;x<12;x+=4)
    {
      for (int y=0;y<2;y++)
        {
          tri->m_tdata[x+y]/=-tri->m_tdata[x+3];
        }
    }
}

void rast::boundFill(iobj* tri)
{
  m_boundBox[0]=tri->m_tdata[0];
  m_boundBox[1]=tri->m_tdata[1];
  m_boundBox[2]=tri->m_tdata[0];
  m_boundBox[3]=tri->m_tdata[1];

  for (int x=4;x<12;x+=4)
    {
      m_boundBox[0]=min(tri->m_tdata[x],m_boundBox[0]);
      m_boundBox[1]=min(tri->m_tdata[x+1],m_boundBox[1]);
      m_boundBox[2]=max(tri->m_tdata[x],m_boundBox[2]);
      m_boundBox[3]=max(tri->m_tdata[x+1],m_boundBox[2]);
    }

  for (int x=0;x<4;x++)
    {
      printf("%f ",m_boundBox[x]);
    }

  int boxSize=(m_boundBox[3]-m_boundBox[1])*(m_boundBox[2]-m_boundBox[0]);

  float x=m_boundBox[0];
  float y=m_boundBox[1];

  while (1)
    {
      fillP(x,y,tri);
      x++;

      if (x>m_boundBox[2])
        {
          x=m_boundBox[0];
          y++;
        }

      if (y>m_boundBox[3])
        {
          break;
        }
    }
  
  /* for (int z=0;z<boxSize;z++) */
  /*   { */
  /*     printf("%f, %f\n",x,y); */
  /*     x++; */

  /*     if (x>m_boundBox[2]) */
  /*       { */
  /*         x=m_boundBox[0]; */
  /*         y++; */
  /*       } */
  /*   } */
}

void rast::fillP(int x,int y,iobj* tri)
{
  
}
