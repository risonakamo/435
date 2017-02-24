#include "iobj.h"

iobj::iobj()
:m_type(0),m_data(NULL),m_colour(NULL),m_next(NULL)
{
  
}

iobj::iobj(int type,double* data,double* colour,iobj* next)
:m_type(type),m_data(data),m_colour(colour),m_next(next)
{

}

void iobj::print()
{
  if (m_type==0)
    {
      cout<<"uninitialised object"<<endl;
      return;
    }

  cout<<"type: "<<m_type<<endl;
  
  if (m_type==1)
    {
      printf("data: %f %f %f %f\n",m_data[0],m_data[1],m_data[2],m_data[3]);
    }

  else if (m_type==2)
    {
      printf("data: ");
      for (int x=0;x<9;x++)
        {
          printf("%f ",m_data[x]);
        }
      cout<<endl;
    }

  printf("colour: ");
  for (int x=0;x<8;x++)
    {
      printf("%f ",m_colour[x]);
    }
  cout<<endl;
}
