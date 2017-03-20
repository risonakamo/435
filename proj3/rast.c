/*rast.c - rasteriser
 khang ngo
 cmsc 435 proj3
 uses data from a rayp obj to perform rasterisation*/

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
      m_background[x]=(unsigned char)(raypars->m_background[x]*255);
      m_backgroundF[x]=raypars->m_background[x];
    }
}

void rast::calcVec()
{
  //lazy check only meant for if default constructor
  //was called
  if (m_dim==0)
    {
      cout<<"rast calcvec: not all variables set"<<endl;
      return;
    }

  //pixel grid size, supports only squares right now
  m_psize=pow(m_dim,2);
  m_img=new double*[m_psize]; //hopefully this inits to null...

  for (int x=0;x<m_psize;x++)
    {
      m_img[x]=NULL;
    }

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
}

//main pipeline process thing
void rast::rasterise()
{
  iobj* cobj=m_adata;

  //for all triangles
  while (1)
    {
      if (!cobj)
        {
          break;
        }

      //M transforms
      Mcam(cobj); 
      MP(cobj);      
      MZdiv(cobj);
      Morth(cobj);
      Mvp(cobj);

      //lighting the vertices
      iLight(cobj);

      //boundbox/filled pixels
      boundFill(cobj);
      
      cobj=cobj->m_next;
    }

  //write img
  writeImg();  
}

//camera transform
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

  for (int x=0;x<3;x++)
    {
      tri->m_zDep[x]=tri->m_tdata[(x*4)+2];
    }
}

//perspective transform
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
      tri->m_tdata[x+2]=(1001*m_hither*m_Mtemp[2])+(((-1000*m_hither)*m_hither)*m_Mtemp[3]);
      tri->m_tdata[x+3]=m_Mtemp[2];
    }
}

//orthogonal transform
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
      tri->m_tdata[x+2]=(((2/999*m_hither))*m_Mtemp[2])+((-1001/999)*m_Mtemp[3]);
    }
}

//viewport transform..or something
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

//Z divide
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

//loop over bound box, filling in img array with
//pixels if it covers
void rast::boundFill(iobj* tri)
{
  //get boundbox and bound box dimensions
  calcBoundBox(tri);  
  int boxSize=(m_boundBox[3]-m_boundBox[1])*(m_boundBox[2]-m_boundBox[0]);

  int x=m_boundBox[0];
  int y=m_boundBox[1];

  //loop over bound box
  while (1)
    {
      //test x y for inside triangle, fill img array
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
}

//calculate bound box from triangle
void rast::calcBoundBox(iobj* tri)
{
  m_boundBox[0]=tri->m_tdata[0];
  m_boundBox[1]=tri->m_tdata[1];
  m_boundBox[2]=tri->m_tdata[0];
  m_boundBox[3]=tri->m_tdata[1];

  for (int x=4;x<12;x+=4)
    {
      m_boundBox[0]=ceil(min(tri->m_tdata[x],m_boundBox[0]));
      m_boundBox[1]=ceil(min(tri->m_tdata[x+1],m_boundBox[1]));
      m_boundBox[2]=ceil(max(tri->m_tdata[x],m_boundBox[2]));
      m_boundBox[3]=ceil(max(tri->m_tdata[x+1],m_boundBox[3]));
    }
}

//calculate bary coords a b r from x y and triangle's vertices
void rast::bCord3(double xpos,double ypos,iobj* tri,double& Ra,double& Rb,double& Rr)
{  
  Ra=bCord3F(1,2,xpos,ypos,tri)/bCord3F(1,2,tri->m_tdata[0],tri->m_tdata[1],tri);

  Rb=bCord3F(2,0,xpos,ypos,tri)/bCord3F(2,0,tri->m_tdata[4],tri->m_tdata[5],tri);

  Rr=bCord3F(0,1,xpos,ypos,tri)/bCord3F(0,1,tri->m_tdata[8],tri->m_tdata[9],tri);
}

//fvv(x,y) function thing from textbook (pg165)
double rast::bCord3F(int v1,int v2,double xpos,double ypos,iobj* tri)
{
  v1*=4;
  v2*=4;
  
  return ((tri->m_tdata[v1+1]-tri->m_tdata[v2+1])*xpos)+
    ((tri->m_tdata[v2]-tri->m_tdata[v1])*ypos)+
    (tri->m_tdata[v1]*tri->m_tdata[v2+1])-
    (tri->m_tdata[v2]*tri->m_tdata[v1+1]);
}

//check if point x y is in tri
//looks at tri's tdata
void rast::fillP(int xpos,int ypos,iobj* tri)
{
  if (xpos>=m_dim || xpos<0 || ypos>=m_dim || ypos<0)
    {
      return;
    }

  double u;
  double v;
  double r;
  bCord3(xpos,ypos,tri,u,v,r);
  
  //if in triangle
  if (u>0 && v>0 && r>0)
    {
      //convert x y to img array index
      int pos=xpos+((m_dim-ypos-1)*m_dim);

      //z depth interpolation
      double zDep=(u*tri->m_zDep[0])+(v*tri->m_zDep[1])+(r*tri->m_zDep[2]);
      
      //if fragment exists and z is closer than current obj, do nothing
      if (m_img[pos] && m_img[pos][3]>zDep)
        {
          return;
        }

      //if nothing at pixel currently
      if (!m_img[pos])
        {
          m_img[pos]=new double[4];
        }            

      //interpolate colour
      intColour(u,v,r,tri);

      //setting colour
      for (int z=0;z<3;z++)
        {
          m_img[pos][z]=m_colourF[z];
        }

      //setting z dep
      m_img[pos][3]=zDep;
    }
}

//write img to file
void rast::writeImg()
{
  FILE* f=fopen(m_ofile.c_str(),"wb");
  fprintf(f,"P6 %i %i 255\n",m_dim,m_dim);
  
  for (int x=0;x<m_psize;x++)
    {
      if (m_img[x])
        {
          for (int y=0;y<3;y++)
            {
              m_colour[y]=(unsigned char)(m_img[x][y]*255);
            }
          
          fwrite(m_colour,1,3,f);
        }

      else
        {
          fwrite(m_background,1,3,f);
        }
    }
}

//calculate vertex colour for a triangle
void rast::iLight(iobj* tri)
{
  ilit* clight; //current light

  //calc triangle normal
  objN(tri);
  
  //for 3 vertices in tri
  for (int v=0;v<9;v+=3)
    {
      clight=m_light; //current light

      //initialise colour vector
      for (int x=0;x<3;x++)
        {
          tri->m_vcolour[v+x]=0;
        }

      //if the triangle has vertex normals (its a pp),
      //use those instead
      if (tri->m_ndata)
        {
          for (int x=0;x<3;x++)
            {
              m_objN[0][x]=tri->m_ndata[x+v];
            }

          /* normalize(m_objN[0]); */
        }
      
      //for eahc light
      while (1)
        {
          if (!clight)
            {
              break;
            }

          //set lray to light point
          for (int x=0;x<3;x++)
            {
              m_lray[x]=clight->m_data[x]-tri->m_data[x+v];
              m_haf[x]=m_lray[x]-(tri->m_data[x+v]-m_from[x]);
            }
          
          normalize(m_haf);
          normalize(m_lray);

          double diff=max(0.0,dot(m_objN[0],m_lray));
          double spec=pow(max(0.0,dot(m_objN[0],m_haf)),tri->m_colour[5]);
          
          for (int x=0;x<3;x++)
            {
              //diffuse+spec light intensity formula thing
              tri->m_vcolour[v+x]+=((tri->m_colour[3]*tri->m_colour[x]*diff)+(tri->m_colour[4]*spec))*(1/pow(m_maxLight,.5));
              
              if (tri->m_vcolour[v+x]>1.0)
                {
                  tri->m_vcolour[v+x]=1;
                }

              if (tri->m_vcolour[v+x]<0.0)
                {
                  tri->m_vcolour[v+x]=0;
                }
            }

          clight=clight->m_next;
        }
    }
}

//calc triangle normal
void rast::objN(iobj* tri)
{
  if (!tri)
    {
      return;
    }

  //triangle and doesnt have normal data (not a pp)
  if (tri->m_type==2 && !tri->m_ndata)
    {
      for (int x=0;x<3;x++)
        {
          m_objN[1][x]=tri->m_data[x]-tri->m_data[x+3];              
          m_objN[2][x]=tri->m_data[x]-tri->m_data[x+6];
        }

      m_objN[0]=cross(m_objN[1],m_objN[2]);
      normalize(m_objN[0]);
      
      return;
    }
}

//interpolate colour
void rast::intColour(double triU,double triV,double triR,iobj* tri)
{
  /* tri->printVcolour(); */

  for (int x=0;x<3;x++)
    {
      m_colourF[x]=tri->m_vcolour[x]*triU;
    }
  
  for (int x=0;x<3;x++)
    {
      m_colourF[x]+=tri->m_vcolour[x+3]*triV;
    }

  for (int x=0;x<3;x++)
    {
      m_colourF[x]+=tri->m_vcolour[x+6]*triR;
    }
  
  for (int x=0;x<3;x++)
    {
      if (m_colourF[x]>1)
        {
          m_colourF[x]=1;
        }
      
      if (m_colourF[x]<0.0000000000000000000000000000000000000000000000000000000000000000000000)
        {
          m_colourF[x]=0;
        }
    }
}
