/*seam.c - main seam object
  khang ngo
  cmsc 435 proj 6
  main seam object.  loads image and does energy calculation,
  seam tracing, and image output. stores image as array of
  pixl objects*/

#include "seam.h"

seam::seam()
{

}

//load cimg and create pixl array
seam::seam(char* inputfile)
:m_inputimg(inputfile),m_height(m_inputimg.height()),m_width(m_inputimg.width()),
 m_minSeam(-1)
{
  m_pixls=new pixl*[m_height*m_width];

  m_inputimg.RGBtoLab();

  int i=0;
  for (int y=0;y<m_height;y++)
  {
    for (int x=0;x<m_width;x++)
    {
      m_pixls[i]=new pixl(m_inputimg(x,y,0),m_inputimg(x,y,1),m_inputimg(x,y,2),i);
      i++;
    }
  }
}

//calc energy for all pixl array
void seam::calcEnergy()
{
  int i=0;
  for (int x=0;x<m_height;x++)
  {
    for (int y=0;y<m_width;y++)
    {
      calcEnergy(y,x,i);
      i++;
    }
  }
}

//calc energy for pixl at x pos, ypos, and index cpixl
void seam::calcEnergy(int xpos,int ypos,int cpixl)
{
  //gradient energy function check around thingy
  if (xpos-1<0)
  {
    t_epixls[0]=m_pixls[cpixl];
  }

  else
  {
    t_epixls[0]=m_pixls[cpixl-1];
  }

  if (xpos+1>=m_width)
  {
    t_epixls[1]=m_pixls[cpixl];
  }

  else
  {
    t_epixls[1]=m_pixls[cpixl+1];
  }

  if (ypos-1<0)
  {
    t_epixls[2]=m_pixls[cpixl];
  }

  else
  {
    t_epixls[2]=m_pixls[xpos+((ypos-1)*m_width)];
  }

  if (ypos+1>=m_height)
  {
    t_epixls[3]=m_pixls[cpixl];
  }

  else
  {
    t_epixls[3]=m_pixls[xpos+((ypos+1)*m_width)];
  }

  m_pixls[cpixl]->m_energy=sqrt(sqrMag((t_epixls[1]->m_lab)-(t_epixls[0]->m_lab))+
                           sqrMag((t_epixls[2]->m_lab)-(t_epixls[3]->m_lab)));

  //if top row dont do previous energy adds
  if (ypos-1<0)
  {
    return;
  }

  //determining minimum previous energy
  double cmin=-1;
  int minparent=-1;
  for (int x=-1;x<=1;x++)
  {
    if (xpos+x<0 || xpos+x>=m_width)
    {
      continue;
    }

    if (cmin<0 || m_pixls[(xpos+x)+((ypos-1)*m_width)]->m_energy<cmin)
    {
      minparent=(xpos+x)+((ypos-1)*m_width);
      cmin=m_pixls[minparent]->m_energy;
    }
  }

  m_pixls[cpixl]->m_energy+=cmin;
  m_pixls[cpixl]->m_parent=minparent;

  if (ypos+1>=m_height && 
      (m_minSeam==-1 || m_pixls[cpixl]->m_energy<m_pixls[m_minSeam]->m_energy))
  {
    m_minSeam=cpixl;
  }
}

//trace minimum seam up
void seam::seamTrace()
{
  seamTrace(m_minSeam);
}

//trace seam with parent index and mark index -1
void seam::seamTrace(int pos)
{
  pixl* c=m_pixls[pos];

  while (1)
  {
    if (!c)
    {
      break;
    }

    c->m_index=-1;

    if (c->m_parent<0)
    {
      break;
    }

    c=m_pixls[c->m_parent];
  }
}

//rebuild pixl array by taking out marked -1s
void seam::rebuildImg()
{
  m_minSeam=-1;
  m_width--;
  m_pixls2=new pixl*[m_width*m_height];

  int i=0;
  for (int x=0;x<m_height*(m_width+1);x++)
  {
    if (m_pixls[x]->m_index>=0)
    {
      m_pixls2[i]=m_pixls[x];
      // m_pixls2[i]->m_energy=-1;
      m_pixls2[i]->m_parent=-1;
      i++;
    }
  }

  delete m_pixls;
  m_pixls=m_pixls2;
}

//debug print all energies
void seam::printEnergy()
{
  int y=0;
  for (int x=0;x<m_width*m_height;x++)
  {
    cout<<m_pixls[x]->m_energy<<" ";

    y++;

    if (y>=m_width)
    {
      cout<<endl;
      y=0;
    }
  }
}

//output pixl array into specified ofile
void seam::outputPixl(const char* ofile)
{
  CImg<double> newimg(m_width,m_height,m_inputimg.depth(),m_inputimg.spectrum(),0);
  
  int i=0;
  for (int y=0;y<m_height;y++)
  {
    for (int x=0;x<m_width;x++)
    {
      newimg(x,y,0)=m_pixls[i]->m_lab[0];
      newimg(x,y,1)=m_pixls[i]->m_lab[1];
      newimg(x,y,2)=m_pixls[i]->m_lab[2];
      i++;
    }
  }

  newimg.LabtoRGB();

  if (strstr(ofile,"png"))
  {
    newimg.save_png(ofile);
  }

  else if (strstr(ofile,"jpg"))
  {
    newimg.save_jpeg(ofile);
  }
}

//transpose pixl array
void seam::rotateImg()
{
  m_pixls2=new pixl*[m_width*m_height];

  int i=0;
  for (int y=0;y<m_height;y++)
  {
    for (int x=0;x<m_width;x++)
    {
      m_pixls2[y+(x*m_height)]=m_pixls[i];
      i++;
    }
  }

  delete m_pixls;
  m_pixls=m_pixls2;

  int t=m_width;
  m_width=m_height;
  m_height=t;
}

//main resize function, do resizing and write to file
void seam::resize(int width,int height,const char* ofile)
{
  int witers=m_width-width;
  int hiters=m_height-height;

  for (int x=0;x<witers;x++)
  {
    calcEnergy();
    seamTrace();
    rebuildImg();
  }

  rotateImg();

  for (int x=0;x<hiters;x++)
  {
    calcEnergy();
    seamTrace();
    rebuildImg();
  }

  rotateImg();

  outputPixl(ofile);
}