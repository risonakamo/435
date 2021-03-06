/*rayd2.c - ray data v2
  khang ngo 
  cmsc 435 proj 1
  handles the calulating part after recieving data
  from rayp object*/

#include "rayd2.h"

using namespace std;

rayd2::rayd2()
:m_from(0,0,0),m_at(0,0,0),m_up(0,0,0),m_angle(0),m_dim(0),
  m_cdata2(NULL),m_pdata(NULL),m_ofile("output.ppm")
{

}

//rayp constructor
//takes data gathered by rayp object
rayd2::rayd2(rayp* raypars)
:m_angle(raypars->m_angle),m_dim(raypars->m_res[0]),m_cdata2(raypars->m_cdata),
  m_pdata(raypars->m_pdata),m_ofile(raypars->m_ofile)
{
  for (int x=0;x<3;x++)
    {
      m_from[x]=raypars->m_from[x];
      m_at[x]=raypars->m_at[x];
      m_up[x]=raypars->m_up[x];
      m_background[x]=raypars->m_background[x]*255;
      m_colour[x]=raypars->m_fill[x]*255;
    }
}

//calculate various vectors
//the letter choices are from class
void rayd2::calcVec()
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
  m_d=mag(m_from-m_at);
  m_m=tan(m_angle*(M_PI/180)*.5)*m_d;

  normalize(m_w);
  normalize(m_u);
  normalize(m_v);
}

//calculate pixel intersection points
//using method from class
void rayd2::genPpoints()
{
  //m_psize was calculated off dimensions earlier
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

//debug print
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

//debug print all calculated pixel points
void rayd2::printPpoints()
{
  for (int x=0;x<m_psize;x++)
    {
      cout<<m_ppointsV[x]<<endl;      
    }

  cout<<endl;
}

//main intersection function, produces output
void rayd2::isect()
{    
  int i;
  
  //linked lists of triangles/spheres
  flink2<float*>* t;
  flink2<float**>* t2;

  //preparing output
  FILE* f=fopen(m_ofile.c_str(),"w");
  fprintf(f,"P6 %d %d 255\n",m_dim,m_dim);

  //for every ray in m_ppointsV
  for (int x=0;x<m_psize;x++)
    {
      //debug progress indicator
      /* printf("\r    \r%.2f%%",((float)x/(float)m_psize)*100); */
      i=0;
      t=m_cdata2;
      t2=m_pdata;

      //for this proj, when sees intersection immediately
      //writes colour to file(doesnt store in big array)
      while (1)
        {
          if (t)
            {
              //intersect every sphere
              if (rSphere(m_ppointsV[x],t->m_data)>=0)
                {
                  i=1;
                  break;
                }

              t=t->m_next;
            }

          if (t2)
            {
              //intersect triangle
              if (rTri(m_ppointsV[x],t2->m_data)==1)
                {
                  i=1;
                  break;
                }

              t2=t2->m_next;
            }

          //no more left
          if (!t && !t2)
            {
              break;
            }
        }

      //found intersection, writing colour
      if (i==1)
        {
          fwrite(m_colour,1,3,f);
        }

      //or write background colour
      else
        {
          fwrite(m_background,1,3,f);
        }
    }
}

//pixel ray vector, sphere array [x,y,z,r]
//sorigin for sphere origin
//using t and discriminent method from the book
float rayd2::rSphere(SlVector3 &ray,float* sOrigin)
{
  m_sflots[0]=0;
  m_sflots[1]=0;
  m_sflots[2]=0;
  m_sflots[3]=0;
  m_sflots[4]=0;

  //solving for abc
  for (int x=0;x<3;x++)
    {
      m_sflots[0]+=pow(ray[x],2);
      m_sflots[1]+=ray[x]*(m_from[x]-sOrigin[x]);
      m_sflots[2]+=pow(sOrigin[x],2);
      m_sflots[3]+=pow(m_from[x],2);
      m_sflots[4]+=sOrigin[x]*m_from[x];
    }

  m_sflots[1]*=2;
  m_sflots[2]=m_sflots[2]+m_sflots[3]+(-2*m_sflots[4]-pow(sOrigin[3],2));

  //discriminentnant:
  //if greater than 0 intersects twice
  //is 0 intersects once (tangent)
  //else no intersect
  //but isect handles this, so just return it
  return pow(m_sflots[1],2)-(4*m_sflots[0]*m_sflots[2]);
}

//overload version
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

//used arrays to be hopefully faster
int rayd2::rTri(SlVector3 &ray,SlVector3* p)
{
  m_rvecs[0]=p[1]-p[0];
  m_rvecs[1]=p[2]-p[0];
  
  m_rvecs[2]=cross(ray,m_rvecs[1]);
  m_rflots[0]=dot(m_rvecs[0],m_rvecs[2]); //determinant

  //if 0 its paralelele
  if (m_rflots[0]==0)
    {
      return 0;
    }

  m_rvecs[3]=m_from-p[0];

  //alpha (or greek r(?) from the book
  m_rflots[1]=dot(m_rvecs[3],m_rvecs[2])/m_rflots[0];

  if (m_rflots[1]<0.0 || m_rflots[1]>1.0)
    {
      return 0;
    }

  m_rvecs[4]=cross(m_rvecs[3],m_rvecs[0]);
  m_rflots[2]=dot(ray,m_rvecs[4])/m_rflots[0]; //beta

  if (m_rflots[2]<0.0 || m_rflots[1]+m_rflots[2]>1.0) 
    {
      return 0;
    }

  //t
  if ((dot(m_rvecs[1],m_rvecs[4])/m_rflots[0])>0.0)
    {
      return 1;
    }

  return 0;
}
