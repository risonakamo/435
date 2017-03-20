/*iobj.c - intersection object rasteriser version
 khang ngo
 cmsc 435 proj3
 contains data for rasterisation triangle.  stores transform data,
 normal data, colour data, depth. acts as linked list*/

#include "iobj.h"

//default constructor
iobj::iobj()
:m_type(0),m_data(NULL),m_colour(NULL),m_next(NULL),m_ndata(NULL)
{
  
}

//set stuff constructor
iobj::iobj(int type,double* data,double* tdata,double* colour,iobj* next)
:m_type(type),m_data(data),m_tdata(tdata),m_colour(colour),m_next(next),
  m_ndata(NULL)
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
      
      if (m_ndata)
        {
          printf("ndata: ");
          for (int x=0;x<9;x++)
            {
              printf("%f ",m_ndata[x]);
            }

          cout<<endl;
        }     
    }

  else if (m_type==3)
    {
      printf("data: ");
      for (int x=0;x<18;x++)
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

//print transform data
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

//print vertex colours
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

//splits 18 array of vertex and normals into seperate arrays
void iobj::splitN()
{
  double* data2=new double[9];
  m_ndata=new double[9];
  
  int z=0;
  for (int x=3;x<21;x+=6)
    {
      for (int y=0;y<3;y++)
        {
          data2[z]=m_data[(x-3)+y];
          m_ndata[z]=m_data[x+y];
          
          z++;
        }
    }

  m_data=data2;
  m_type=2;
}
