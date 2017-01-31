#include "rayd.h"

using namespace std;

rayd::rayd()
:m_mode(0),m_mc(0),m_angle(0),m_hither(0)
{
  int x;

  for (x=0;x<3;x++)
    {
      m_background[x]=0;
      m_at[x]=0;
      m_up[x]=0;      
    }

  for (x=0;x<2;x++)
    {
      m_res[x]=0;
    }

  for (x=0;x<8;x++)
    {
      m_fill[x]=0;
    }
}

//a for argument
void rayd::argParse(string a)
{
  if (m_mode==10)
    {
      
    }
  
  //currently does not include L for light!!!
  if (m_mode==1 || m_mode==2 || m_mode==3
      || m_mode==4 || m_mode==7 || m_mode==9)
    {
      arrayParse(m_mode,a);
    }

  if (m_mode==5)
    {
      m_angle=atoi(a.c_str());
      m_mode=0;
      return;
    }

  if (m_mode==6)
    {
      m_hither=atoi(a.c_str());
      m_mode=0;
      return;
    }
  
  if (a=="b")
    {
      m_mode=1;
      m_mc=0;
      return;
    }

  if (a=="from")
    {
      m_mode=2;
      m_mc=0;
      return;
    }

  if (a=="at")
    {
      m_mode=3;
      m_mc=0;
      return;
    }

  if (a=="up")
    {
      m_mode=4;
      m_mc=0;
      return;
    }

  if (a=="angle")
    {
      m_mode=5;
      m_mc=0;
      return;
    }

  if (a=="hither")
    {
      m_mode=6;
      m_mc=0;
      return;
    }

  if (a=="resolution")
    {
      m_mode=7;
      m_mc=0;
      return;
    }

  if (a=="l")
    {
      m_mode=8;
      m_mc=0;
      return;
    }

  if (a=="f")
    {
      m_mode=9;
      m_mc=0;
      return;
    }

  if (a=="p")
    {
      m_mode=10;
      m_mc=0;
      return;
    }
}

//tmode=type mode (0=float)
//mmode=mode mode, same usage as m_mode
//msize=mode size, size of array to be filled
void rayd::arrayParse(int mmode,string a)
{
  if (mmode==0)
    {
      return;
    }
  
  int msize=arrayParseFill(mmode,a);

  m_mc++;

  if (m_mc>msize-1)
    {
      m_mc=0;
      m_mode=0;
    }
}

//helper for arrayParse because i dont
//like else ifs
//puts things into arrays, returns the size
//of the array being filled up so the upper
//arrayparse knows when to stop
int rayd::arrayParseFill(int mmode,string a)
{
  if (mmode==1)
    {
      m_background[m_mc]=atof(a.c_str());
      return 3;
    }

  if (mmode==2)
    {
      m_from[m_mc]=atof(a.c_str());
      return 3;          
    }
  
  if (mmode==3)
    {
      m_at[m_mc]=atof(a.c_str());
      return 3;          
    }

  if (mmode==4)
    {
      m_up[m_mc]=atof(a.c_str());
      return 3;          
    }

  if (mmode==7)
    {
      m_res[m_mc]=atoi(a.c_str());
      return 2;          
    }

  if (mmode==9)
    {
      m_fill[m_mc]=atof(a.c_str());
      return 8;
    }
}

void rayd::printd()
{
  printf("b %f %f %f\n",m_background[0],m_background[1],m_background[2]);
  printf("from %f %f %f\n",m_from[0],m_from[1],m_from[2]);
  printf("at %f %f %f\n",m_at[0],m_at[1],m_at[2]);
  printf("up %f %f %f\n",m_up[0],m_up[1],m_up[2]);
  printf("angle %i\n",m_angle);
  printf("hither %i\n",m_hither);
  printf("res %i %i\n",m_res[0],m_res[1]);
  printf("fill %i %i %i %i %i %i %i %i\n",m_fill[0],m_fill[1],m_fill[2],m_fill[3],m_fill[4],m_fill[5],m_fill[6],m_fill[7]);
}
