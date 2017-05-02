#include "seam.h"

seam::seam()
{

}

seam::seam(char* inputfile)
:m_inputimg(inputfile),m_height(m_inputimg.height()),m_width(m_inputimg.width())
{
  m_pixls=new pixl*[m_height*m_width];

  int i=0;
  for (int x=0;x<m_width;x++)
  {
    for (int y=0;y<m_height;y++)
    {
      m_pixls[i]=new pixl(m_inputimg(x,y,0),m_inputimg(x,y,1),m_inputimg(x,y,2));
      i++;
    }
  }

  std::cout<<m_pixls[0]->m_lab<<std::endl;
}