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
  m_img=new float*[m_psize]; //hopefully this inits to null...

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

void rast::rasterise()
{
  iobj* cobj=m_adata;
  
  while (1)
    {
      if (!cobj)
        {
          break;
        }
      
      Mcam(cobj);
      /* /\*--tdataprinter--*\/ */
      /* /\* cobj->print(); *\/ */
      /* cobj->printTdata(); */
      /* printf("\n"); */
      /* /\*----------------*\/            */
      MP(cobj);      
      MZdiv(cobj);
      Morth(cobj);
      Mvp(cobj);
      iLight(cobj);

      boundFill(cobj);
      
      cobj=cobj->m_next;
    }

  writeImg();  
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

      if (x==0)
        {
          tri->m_zDep=tri->m_tdata[2];
          /* printf("z=%f\n",tri->m_zDep); */
        }

      else
        {
          tri->m_zDep=max(tri->m_zDep,tri->m_tdata[x+2]);
        }
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
      tri->m_tdata[x+2]=(1001*m_hither*m_Mtemp[2])+(((-1000*m_hither)*m_hither)*m_Mtemp[3]);
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
      tri->m_tdata[x+2]=(((2/999*m_hither))*m_Mtemp[2])+((-1001/999)*m_Mtemp[3]);
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

void rast::calcBoundBox(iobj* tri)
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
      m_boundBox[3]=max(tri->m_tdata[x+1],m_boundBox[3]);
    }

  /* for (int x=0;x<4;x++) */
  /*   { */
  /*     printf("%f ",m_boundBox[x]); */
  /*   } */
}

void rast::boundFill(iobj* tri)
{
  calcBoundBox(tri);

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
  /*     fillP(x,y,tri); */
  /*     x++; */

  /*     if (x>m_boundBox[2]) */
  /*       { */
  /*         x=m_boundBox[0]; */
  /*         y++; */
  /*       } */
  /*   } */
}

//check if point x y is in tri
//looks at tri's tdata
void rast::fillP(int x,int y,iobj* tri)
{
  if (x>m_dim || x<0 || y>m_dim || y<0)
    {
      return;
    }
  
  //setting vectors
  for (int z=0;z<2;z++)
    {
      m_baryT[0][z]=tri->m_tdata[8+z]-tri->m_tdata[z];
      m_baryT[1][z]=tri->m_tdata[4+z]-tri->m_tdata[z];
    }
  
  m_baryT[2][0]=x-tri->m_tdata[0];
  m_baryT[2][1]=y-tri->m_tdata[1];
  
  for (int z=0;z<3;z++)
    {
      m_baryT[z][2]=0;
    }

  m_baryTF[0]=dot(m_baryT[0],m_baryT[0]);
  m_baryTF[1]=dot(m_baryT[0],m_baryT[1]);
  m_baryTF[2]=dot(m_baryT[0],m_baryT[2]);
  m_baryTF[3]=dot(m_baryT[1],m_baryT[1]);
  m_baryTF[4]=dot(m_baryT[1],m_baryT[2]);

  float id=1/(m_baryTF[0]*m_baryTF[3]-m_baryTF[1]*m_baryTF[1]);
  float u=(m_baryTF[3]*m_baryTF[2]-m_baryTF[1]*m_baryTF[4])*id;
  float v=(m_baryTF[0]*m_baryTF[4]-m_baryTF[1]*m_baryTF[2])*id;

  //if in triangle
  if (u>=0 && v>=0 && u+v<1)
    {
      int pos=x+((m_dim-y-1)*m_dim);
      /* printf("%i\n",pos); */

      float zDep=((1-u-v)*tri->m_data[2])+(u*tri->m_data[5])+(v*tri->m_data[8]);
      
      //if fragment exists and z is closer than current obj
      if (m_img[pos] && m_img[pos][3]>zDep)
        {
          /* printf("%f %f\n",m_img[pos]->m_zDep,tri->m_zDep); */
          return;
        }

      //if no img
      if (!m_img[pos])
        {
          m_img[pos]=new float[4];
        }

      /* //tempory solid colour */
      /* for (int z=0;z<3;z++) */
      /*   { */
      /*     m_img[pos][z]=tri->m_colour[z]; */
      /*   } */
      
      intColour(u,v,tri);
          
      for (int z=0;z<3;z++)
        {
          m_img[pos][z]=m_colourF[z];
        }

      m_img[pos][3]=zDep;
    }
}

void rast::writeImg()
{
  FILE* f=fopen(m_ofile.c_str(),"w");  
  fprintf(f,"P6 %d %d 255\n",m_dim,m_dim);
  
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

void rast::iLight(iobj* tri)
{
  iobj* clight=m_light; //current light

  objN(tri);
  
  //for 3 vertices in tri
  for (int v=0;v<9;v+=3)
    {
      for (int x=0;x<3;x++)
        {
          tri->m_vcolour[v+x]=0;
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
              m_haf[x]=m_lray[x]-(m_from[x]-tri->m_data[x+v]);
            }
            
          normalize(m_haf);
          normalize(m_lray);
          normalize(m_objN[0]);

          double diff=max(0.0,dot(m_objN[0],m_lray));
          double spec=pow(max(0.0,dot(m_objN[0],m_haf)),tri->m_colour[5]);
          
          for (int x=0;x<3;x++)
            {
              //diffuse+spec light intensity formula thing
              tri->m_vcolour[v+x]+=(((tri->m_colour[3]*tri->m_colour[x]*diff)+(tri->m_colour[4]*spec))*(((1/pow(m_maxLight,.5)))));

              if (tri->m_vcolour[v+x]>1)
                {
                  tri->m_vcolour[v+x]=1;
                }

              if (tri->m_vcolour[v+x]<0)
                {
                  tri->m_vcolour[v+x]=0;
                }
            }

          clight=clight->m_next;
        }      
    }   
}

void rast::objN(iobj* tri)
{
  if (!tri)
    {
      return;
    }

  //triangle
  if (tri->m_type==2)
    {
      //triangles are stored in size 9 array
      for (int x=0;x<3;x++)
        {
          m_objN[1][x]=tri->m_data[x]-tri->m_data[x+3];              
          m_objN[2][x]=tri->m_data[x]-tri->m_data[x+6];
        }

      m_objN[0]=cross(m_objN[1],m_objN[2]);
      return;
    }
}

void rast::intColour(float& triU,float& triV,iobj* tri)
{
  for (int x=0;x<3;x++)
    {
      m_colourF[x]=tri->m_colour[x]*(1-triU-triV);
    }

  for (int x=0;x<3;x++)
    {
      m_colourF[x]+=tri->m_colour[x+3]*triU;
    }

  for (int x=0;x<3;x++)
    {
      m_colourF[x]+=tri->m_colour[x+6]*triV;
    }

  for (int x=0;x<3;x++)
    {
      if (m_colourF[x]>1)
        {
          m_colourF[x]=1;
        }

      if (m_colourF[x]<0);
      {
        m_colourF[x]=0;
      }
    }
}
