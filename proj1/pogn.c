#include "pogn.h"

using namespace std;

pogn::pogn()
:m_p(0),m_ms(9)
{
  m_d=new float[m_ms];  
}

//v for vertices
pogn::pogn(int v)
:m_p(0),m_ms(v*3)
{
  m_d=new float[m_ms];

  for (int x=0;x<m_ms;x++)
    {
      m_d[x]=0;
    }
}

pogn::pogn(string v)
:m_p(0)
{
  m_ms=atoi(v.c_str());
  m_ms=m_ms*3;
  
  m_d=new float[m_ms];

  for (int x=0;x<m_ms;x++)
    {
      m_d[x]=0;
    }
}

pogn::~pogn()
{
  delete[] m_d;
}

void pogn::load(float p)
{
  _load(p);
}

void pogn::load(string p)
{
  _load(atof(p.c_str()));
}

void pogn::_load(float p)
{
  if (m_p>=m_ms)
    {
      cout<<"polygon error: max points inputted"<<endl;
      return;
    }
  
  m_d[m_p]=p;
  m_p++;
}

void pogn::vprint()
{
  int c=-1;
  
  cout<<"p"<<endl;
  for (int x=0;x<m_ms;x++)
    {
      if (c>=2)
        {
          cout<<endl;
          c=-1;
        }

      c++;

      if (c!=0)
        {
          cout<<" ";
        }
      
      cout<<m_d[x];
    }

  cout<<endl;
}
