/*iobj.c - intersection object
 khang ngo
 cmsc 435 proj2
 represents different types of objects used in intersecting,
 including spheres polygons and lights. stores data as 1d array
 and doubles as linked list*/

#include "iobj.h"

//default constructor
iobj::iobj()
:m_type(0),m_data(NULL),m_colour(NULL),m_next(NULL)
{
  
}

//set stuff constructor
iobj::iobj(int type,double* data,double* tdata,double* colour,iobj* next)
:m_type(type),m_data(data),m_tdata(tdata),m_colour(colour),m_next(next),
  m_zDep(1)
{
  for (int x=0;x<9;x++)
    {
      m_vcolour[x]=0;
    }
}

//debug to read data for some types
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

void iobj::printTdata()
{
  int y=0;
  for (int x=0;x<12;x++)
    {
      printf("%f ",m_tdata[x]);

      y++;
      if (y>3)
        {
          y=0;
          printf("\n");
        }
    }
}

void iobj::printVcolour()
{
  int y=0;
  for (int x=0;x<9;x++)
    {
      printf("%f ",m_vcolour[x]);

      y++;
      if (y>2)
        {
          y=0;
          printf("\n");
        }
    }
}