/*rayd2.c - ray data v2
  khang ngo 
  cmsc 435 proj 1
  handles the calulating part after recieving data
  from rayp object*/

#include "rayd2.h"

using namespace std;

rayd2::rayd2()
:m_from(0,0,0),m_at(0,0,0),m_up(0,0,0),m_angle(0),m_dim(0),
  m_ofile("output.ppm"),m_adata(NULL)
{

}

//rayp constructor
//takes data gathered by rayp object
rayd2::rayd2(rayp* raypars)
:m_angle(raypars->m_angle),m_dim(raypars->m_res[0]),
  m_ofile(raypars->m_ofile),m_adata(raypars->m_adata),
  m_light(raypars->m_light),m_maxLight(raypars->m_maxLight)
{
  for (int x=0;x<3;x++)
    {
      m_from[x]=raypars->m_from[x];
      m_at[x]=raypars->m_at[x];
      m_up[x]=raypars->m_up[x];
      m_background[x]=raypars->m_background[x]*255;
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
  //preparing output
  FILE* f=fopen(m_ofile.c_str(),"w");  
  fprintf(f,"P6 %d %d 255\n",m_dim,m_dim);

  float i=-1; //i intersection value
  float t=-1; //t value
  int found=0; //found intersection
  iobj* obj; //current obj
  iobj* cobj=NULL; //closest object

  SlVector3 iRay;
  
  //for every ray in m_ppointsV
  for (int x=0;x<m_psize;x++)
    {
      //debug progress indicator
      printf("\r    \r%.2f%%",((float)x/(float)m_psize)*100);
      
      obj=m_adata;
      found=0;
      while (1)
        {
          if (!obj)
            {
              break;
            }

          if (obj->m_type==1)
            {              
              i=rSphere(m_ppointsV[x],m_from,obj->m_data);
            }

          else if (obj->m_type==2)
            {
              i=rTri(m_ppointsV[x],m_from,obj->m_data);
            }

          if ((obj->m_type==1 && i>=0.0) || (obj->m_type==2 && i>0.0))
            {
              if (found==0)
                {
                  found=1;
                  t=i;
                  cobj=obj;
                  iRay=m_ppointsV[x];
                }

              else
                {
                  t=min(t,i);

                  if (t==i)
                    {
                      cobj=obj;
                      iRay=m_ppointsV[x];
                    }
                }
            }         
          
          obj=obj->m_next;         
        }

      //found intersection, writing colour
      //CHANGE THIS LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      if (found==1)
        {
          m_colourF[0]=cobj->m_colour[0]*.5;
          m_colourF[1]=cobj->m_colour[1]*.5;
          m_colourF[2]=cobj->m_colour[2]*.5;

          /* m_colourF[0]=0; */
          /* m_colourF[1]=0; */
          /* m_colourF[2]=0; */

          iLight(iRay,m_from,t,cobj);
          
          m_colour[0]=(unsigned int)(m_colourF[0]*255);
          m_colour[1]=(unsigned int)(m_colourF[1]*255);
          m_colour[2]=(unsigned int)(m_colourF[2]*255);

          /* for (int x=0;x<3;x++) */
          /*   { */
          /*     cout<<(int)m_colour[x]<<endl; */
          /*   } */
          
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
float rayd2::rSphere(SlVector3 &ray,SlVector3 &from,float* sOrigin)
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
      m_sflots[1]+=ray[x]*(from[x]-sOrigin[x]);
      m_sflots[2]+=pow(sOrigin[x],2);
      m_sflots[3]+=pow(from[x],2);
      m_sflots[4]+=sOrigin[x]*from[x];
    }

  m_sflots[1]*=2;
  m_sflots[2]=m_sflots[2]+m_sflots[3]+(-2*m_sflots[4]-pow(sOrigin[3],2));

  //discriminentnant:
  //if greater than 0 intersects twice
  //is 0 intersects once (tangent)
  //else no intersect
  if (pow(m_sflots[1],2)-(4*m_sflots[0]*m_sflots[2])<0.0)
    {
      return -1;
    }

  //returning t if intersect
  return ((-m_sflots[1])-pow((pow(m_sflots[1],2)-(4*m_sflots[0]*m_sflots[2])),.5))/(2*m_sflots[0]);
}

//overload version
float rayd2::rTri(SlVector3 &ray,SlVector3 &from,float* p)
{
  int z=0;
  SlVector3 pgons[3];
  for (int x=0;x<3;x++)
    {
      for (int y=0;y<3;y++)
        {
          pgons[x][y]=p[z];
          z++;
        }
    }

  return rTri(ray,from,pgons);
}

//used arrays to be hopefully faster
float rayd2::rTri(SlVector3 &ray,SlVector3 &from,SlVector3* p)
{
  m_rvecs[0]=p[1]-p[0];
  m_rvecs[1]=p[2]-p[0];
  
  m_rvecs[2]=cross(ray,m_rvecs[1]);
  m_rflots[0]=dot(m_rvecs[0],m_rvecs[2]); //determinant

  //if 0 its paralelele
  if (m_rflots[0]==0)
    {
      return -1;
    }

  m_rvecs[3]=from-p[0];

  //alpha (or greek r(?) from the book
  m_rflots[1]=dot(m_rvecs[3],m_rvecs[2])/m_rflots[0];

  if (m_rflots[1]<0.0 || m_rflots[1]>1.0)
    {
      return -1;
    }

  m_rvecs[4]=cross(m_rvecs[3],m_rvecs[0]);
  m_rflots[2]=dot(ray,m_rvecs[4])/m_rflots[0]; //beta

  if (m_rflots[2]<0.0 || m_rflots[1]+m_rflots[2]>1.0) 
    {
      return -1;
    }

  return dot(m_rvecs[1],m_rvecs[4])/m_rflots[0];
  
  //t
  /* if ((dot(m_rvecs[1],m_rvecs[4])/m_rflots[0])>0.0) */
  /*   { */
  /*     return 1; */
  /*   } */

  /* return 0; */
}

void rayd2::iLight(SlVector3 &ray,SlVector3 &from,float t,iobj* cobj)
{
  iobj* obj;
  iobj* clight=m_light; //current light
  int i=0; //intersections

  float diff; //diffuse
  float spec; //specular
  

  m_ipoint=from+(t*ray);
  objN(cobj);
  m_ipoint+=m_objN[0]*.05;

  //for eahc light
  while (1)
    {
      if (!clight)
        {
          return;
        }

      i=0;      
      obj=m_adata;

      //set lray to light point
      for (int x=0;x<3;x++)
        {
          m_lray[x]=clight->m_data[x];
        }
      
      //set lray to actual lray
      m_lray=m_lray-m_ipoint;
      m_haf=m_lray-ray;
      normalize(m_haf);
      normalize(m_lray);
      normalize(m_objN[0]);

      //for each object until 1st intersection with anything
      while (1)
        {
          if (!obj)
            {
              break;
            }


          if (obj->m_type==1 && rSphere(m_lray,m_ipoint,obj->m_data)>=0.0)
            {
              i++;
              break;
            }

          if (obj->m_type==2 && rTri(m_lray,m_ipoint,obj->m_data)>0.0)
            {
              i++;
              break;
            }
      
          obj=obj->m_next;
        }

      //lighted object
      if (i==0)
        {
          diff=max(0.0,dot(m_objN[0],m_lray));
          spec=pow(max(0.0,dot(m_objN[0],m_haf)),cobj->m_colour[5]);

          for (int x=0;x<3;x++)
            {
              m_colourF[x]+=((cobj->m_colour[3]*m_colourF[x]*diff)+(cobj->m_colour[4]*spec))*(1/pow((float)m_maxLight,.5));

              if (m_colourF[x]>1)
                {
                  m_colourF[x]=1;
                }

              if (m_colourF[x]<0)
                {
                  m_colourF[x]=0;
                }
            }
        }

      /* else */
      /*   { */
      /*     for (int x=0;x<3;x++) */
      /*       { */
      /*         m_colourF[x]*=.5; */
      /*       } */
      /*   } */

      clight=clight->m_next;
    }

  /* //tempoary colour calc */
  /* float a; */
  /* if (i!=0) */
  /*   { */
  /*     for (int x=0;x<3;x++) */
  /*       { */
  /*         a=m_colour[x]; */

  /*         if (i==2) */
  /*           { */
  /*             a*=.25; */
  /*           } */

  /*         else */
  /*           { */
  /*             a*=.5; */
  /*           } */
          
  /*         m_colour[x]=(int)a; */
  /*       } */

  /*     return; */
  /*   } */
}

//calculate obj normal and put in m_objN
void rayd2::objN(iobj* obj)
{
  if (!obj)
    {
      return;
    }

  //triangle
  if (obj->m_type==2)
    {
      for (int x=0;x<3;x++)
        {
          m_objN[1][x]=obj->m_data[x];
          m_objN[2][x]=obj->m_data[x+3];
        }

      m_objN[0]=cross(m_objN[1],m_objN[2]);
      return;
    }

  //sphere
  if (obj->m_type==1)
    {
      for (int x=0;x<3;x++)
        {
          m_objN[0][x]=m_ipoint[x]-(obj->m_data[x]);
        }
    }
}
