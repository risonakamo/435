#include "seam.h"

seam::seam()
{

}

seam::seam(char* inputfile)
:m_inputimg(inputfile),m_height(m_inputimg.height()),m_width(m_inputimg.width()),
 m_maxEnergy(-1)
{
  m_pixls=new pixl*[m_height*m_width];

  // m_inputimg.RGBtoLab();

  int i=0;
  for (int y=0;y<m_height;y++)
  {
    for (int x=0;x<m_width;x++)
    {
      m_pixls[i]=new pixl(m_inputimg(x,y,0),m_inputimg(x,y,1),m_inputimg(x,y,2));
      i++;
    }
  }

  i=0;
  for (int x=0;x<m_height;x++)
  {
    for (int y=0;y<m_width;y++)
    {
      calcEnergy(y,x,i);
      // std::cout<<m_pixls[i]->m_energy<<std::endl;
      i++;
    }
  }

  std::cout<<m_maxEnergy<<std::endl;
  std::cout<<m_pixls[0]->m_lab<<std::endl;
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

  std::cout<<m_pixls[cpixl]->m_energy<<std::endl;                         

  m_maxEnergy=max(m_maxEnergy,m_pixls[cpixl]->m_energy);                          
}

void seam::outputgrey()
{
   m_inputimg.LabtoRGB();

  int i=0;
  double a;
  for (int x=0;x<m_width;x++)
  {
    for (int y=0;y<m_height;y++)
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