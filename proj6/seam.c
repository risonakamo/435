#include "seam.h"

seam::seam()
{

}

seam::seam(char* inputfile)
:m_inputimg(inputfile),m_height(m_inputimg.height()),m_width(m_inputimg.width()),
 m_maxEnergy(-1),m_minSeam(-1)
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

  // std::cout<<m_maxEnergy<<std::endl;
  // std::cout<<m_pixls[0]->m_lab<<std::endl;
}

void seam::calcEnergy(int grey)
{
  int i=0;
  for (int x=0;x<m_height;x++)
  {
    for (int y=0;y<m_width;y++)
    {
      calcEnergy(y,x,i,grey);
      // std::cout<<m_pixls[i]->m_energy<<std::endl;
      i++;
    }
  }
}

void seam::calcEnergy(int xpos,int ypos,int cpixl,int grey)
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
    // std::cout<<"trigger"<<std::endl;
    t_epixls[3]=m_pixls[cpixl];
  }

  else
  {
    t_epixls[3]=m_pixls[xpos+((ypos+1)*m_width)];
  }

  // for (int x=0;x<4;x++)
  // {
  //   std::cout<<t_epixls[x]->m_lab<<std::endl;
  // }
  // std::cout<<std::endl;

  m_pixls[cpixl]->m_energy=pow(sqrMag((t_epixls[1]->m_lab)-(t_epixls[0]->m_lab))+
                           sqrMag((t_epixls[2]->m_lab)-(t_epixls[3]->m_lab)),.5);

  // std::cout<<m_pixls[cpixl]->m_energy<<std::endl;                         

  m_maxEnergy=max(m_maxEnergy,m_pixls[cpixl]->m_energy);                          

  //if top row or doing greyscale dont add previous energies
  if (ypos-1<0 || grey!=0)
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

    if (cmin==-1 || m_pixls[(xpos+x)+((ypos-1)*m_width)]->m_energy<cmin)
    {
      cmin=m_pixls[(xpos+x)+((ypos-1)*m_width)]->m_energy;
      minparent=(xpos+x)+((ypos-1)*m_width);
    }
  }

  // cout<<cmin<<" "<<minparent<<endl;

  m_pixls[cpixl]->m_energy+=cmin;
  m_pixls[cpixl]->m_parent=minparent;

  if (ypos+1>=m_height && (m_minSeam==-1 || m_pixls[cpixl]->m_energy<m_pixls[m_minSeam]->m_energy))
  {
    m_minSeam=cpixl;
  }

  // cout<<m_pixls[cpixl]->m_energy<<" "<<m_minSeam<<endl;

  // //top
  // if (ypos-1<0)
  // {
  //   return;
  // }

  // //far left edge
  // if (xpos-1<0)
  // {
  //   m_pixls[cpixl]->m_energy+=min(m_pixls[xpox+((ypos-1)*m_width)]->m_energy,
  //                                 m_pixls[(xpos+1)+((ypos-1)*m_width)]->m_energy);
  // }

  // //far right edge
  // else if (xpos+1>=m_width)
  // {
  //   m_pixls[cpixl]->m_energy+=min(m_pixls[xpox+((ypos-1)*m_width)]->m_energy,
  //                                 m_pixls[(xpos-1)+((ypos-1)*m_width)]->m_energy);
  // }

  // //normal
  // else
  // {
  //   m_pixls[cpixl]->m_energy+=min(m_pixls[xpox+((ypos-1)*m_width)]->m_energy,
  //                                 m_pixls[(xpos+1)+((ypos-1)*m_width)]->m_energy,
  //                                 m_pixls[(xpos-1)+((ypos-1)*m_width)]->m_energy);
  // }
}

void seam::outputgrey()
{
   m_inputimg.LabtoRGB();

  int i=0;
  double a;
  for (int y=0;y<m_height;y++)
  {
    for (int x=0;x<m_width;x++)
    {
      // std::cout<<m_pixls[i]->m_energy<<std::endl;

      a=(m_pixls[i]->m_energy/m_maxEnergy)*255;

      // std::cout<<a<<std::endl;

      m_inputimg(x,y,0)=a;
      m_inputimg(x,y,1)=a;
      m_inputimg(x,y,2)=a;

      i++;
    }
  }

  m_inputimg.save_png("bob.png");
}

void seam::seamTrace()
{
  m_inputimg.LabtoRGB();

  // for (int x=0;x<m_width;x++)
  // {
  //   seamTrace(x+((m_height-1)*m_width));
  // }

  seamTrace(m_minSeam);

  m_inputimg.save_png("bob2.png");
}

void seam::seamTrace(int pos)
{
  pixl* c=m_pixls[pos];

  while (1)
  {
    if (!c || c->m_parent<0)
    {
      break;
    }

    m_inputimg(c->m_pos[0],c->m_pos[1],0)=0;
    m_inputimg(c->m_pos[0],c->m_pos[1],1)=0;
    m_inputimg(c->m_pos[0],c->m_pos[1],2)=0;

    c=m_pixls[c->m_parent];
  }
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