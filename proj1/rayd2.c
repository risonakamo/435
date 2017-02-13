#include "rayd2.h"

using namespace std;

rayd2::rayd2()
:m_from(0,0,0),m_at(0,0,0),m_up(0,0,0),m_angle(0),m_dim(0),
  m_cdata2(NULL),m_pdata(NULL)
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

rayd2::rayd2(rayp* raypars)
:m_angle(raypars->m_angle),m_dim(raypars->m_res[0]),m_cdata2(raypars->m_cdata),
  m_pdata(raypars->m_pdata)
{
  for (int x=0;x<3;x++)
    {
      m_from[x]=raypars->m_from[x];
      m_at[x]=raypars->m_at[x];
      m_up[x]=raypars->m_up[x];      
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

/* void rayd2::loadCircles(float** cdata,int size) */
/* { */
/*   m_csize=size; */
/*   m_cdata=cdata; */
/* } */

void rayd2::loadCircles(flink2<float*>* cdata)
{
  m_cdata2=cdata;
}

void rayd2::printPpoints()
{
  for (int x=0;x<m_psize;x++)
    {
      cout<<m_ppointsV[x]<<endl;      
    }

  cout<<endl;
}

void rayd2::iSphere()
{

  int i;
  flink2<float*>* t;
  flink2<float**>* t2;
  FILE* f=fopen("test.ppm","w");
  fprintf(f,"P3 %d %d 255\n",m_dim,m_dim);
  for (int x=0;x<m_psize;x++)
    {
      /* for (int y=0;y<m_csize;y++) */
      /*   { */
      /*     rSphere(m_ppointsV[x],m_cdata[y]); */
      /*   } */

      printf("\r    \r%.2f%%",((float)x/(float)m_psize)*100);
      i=0;
      t=m_cdata2;
      t2=m_pdata;
      while (1)
        {
          if (t)
            {
              if (rSphere(m_ppointsV[x],t->m_data)>=0)
                {
                  i=1;
                  break;
                }

              t=t->m_next;
            }

          if (t2)
            {
              if (rTri(m_ppointsV[x],t2->m_data)==1)
                {
                  i=1;
                  break;
                }

              t2=t2->m_next;
            }

          if (!t && !t2)
            {
              break;
            }
        }
      
      if (i==1)
        {
          fprintf(f,"255 255 255 ");
        }

      else
        {
          fprintf(f,"0 0 0 ");
        }
    }
}

//pixel ray vector, sphere array [x,y,z,r]
//sorigin for sphere origin
float rayd2::rSphere(SlVector3 ray,float* sOrigin)
{
  float a=0;
  float b=0;
  float c1=0;
  float c2=0;
  float c3=0;
  for (int x=0;x<3;x++)
    {
      a+=pow(ray[x],2);
      b+=ray[x]*(m_from[x]-sOrigin[x]);
      c1+=pow(sOrigin[x],2);
      c2+=pow(m_from[x],2);
      c3+=sOrigin[x]*m_from[x];
    }

  b*=2;
  c1=c1+c2+(-2*c3-pow(sOrigin[3],2));

  float dis=pow(b,2)-(4*a*c1);
  
  /* cout<<"rsphere:"<<dis<<endl; */
  return dis;
}

int rayd2::rTri(SlVector3 &ray,float** p)
{
  SlVector3 pgons[3];
  for (int x=0;x<3;x++)
    {
      for (int y=0;y<3;y++)
        {
          pgons[x][y]=p[x][y];
        }
    }

  int a=rTri(ray,pgons);
  return a;
}

//uses arrays for efficiency
int rayd2::rTri(SlVector3 &ray,SlVector3* p)
{
  m_rvecs[0]=p[1]-p[0];
  m_rvecs[1]=p[2]-p[0];
  
  m_rvecs[2]=cross(ray,m_rvecs[1]);
  m_rflots[0]=dot(m_rvecs[0],m_rvecs[2]);

  if (m_rflots[0]==0)
    {
      return 0;
    }

  m_rvecs[3]=m_from-p[0];
  m_rflots[1]=dot(m_rvecs[3],m_rvecs[2])/m_rflots[0];

  if (m_rflots[1]<0.0 || m_rflots[1]>1.0)
    {
      return 0;
    }

  m_rvecs[4]=cross(m_rvecs[3],m_rvecs[0]);
  m_rflots[2]=dot(ray,m_rvecs[4])/m_rflots[0];

  if (m_rflots[2]<0.0 || m_rflots[1]+m_rflots[2]>1.0)
    {
      return 0;
    }

  if ((dot(m_rvecs[1],m_rvecs[4])/m_rflots[0])>0.0)
    {
      return 1;
    }

  return 0;
}
