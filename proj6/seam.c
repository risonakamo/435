#include "seam.h"

seam::seam()
{

}

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
      m_pixls[i]=new pixl(m_inputimg(x,y,0),m_inputimg(x,y,1),m_inputimg(x,y,2),x,y,i);
      i++;
    }
  }
}

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

void seam::calcEnergy(int xpos,int ypos,int cpixl)
{
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

  m_pixls[cpixl]->m_energy=pow(sqrMag((t_epixls[1]->m_lab)-(t_epixls[0]->m_lab))+
                           sqrMag((t_epixls[2]->m_lab)-(t_epixls[3]->m_lab)),.5);

  //if top row or doing greyscale dont add previous energies
  if (ypos-1<0)
  {
    return;
  }

  double cmin=-1;
  int minparent=-1;
  for (int x=-1;x<=1;x++)
  {
    if (xpos+x<0 || xpos+x>=m_width)
    {
      continue;
    }

    if (cmin==-1 || m_pixls[(xpos+x)+((ypos-1)*m_width)]->m_energy<=cmin)
    {
      cmin=m_pixls[(xpos+x)+((ypos-1)*m_width)]->m_energy;
      minparent=(xpos+x)+((ypos-1)*m_width);
    }
  }

  m_pixls[cpixl]->m_energy+=cmin;
  m_pixls[cpixl]->m_parent=minparent;

  if (ypos+1>=m_height && 
      (m_minSeam==-1 || m_pixls[cpixl]->m_energy<=m_pixls[m_minSeam]->m_energy))
  {
    m_minSeam=cpixl;
  }
}


void seam::seamTrace()
{
  seamTrace(m_minSeam);
}

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

    else
    {
      
    }
  }

  delete m_pixls;
  m_pixls=m_pixls2;
}

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