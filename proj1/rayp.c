//rayp.c

#include "rayp.h"

using namespace std;

rayp::rayp()
:m_mode(0),m_mc(0),m_angle(0),m_hither(0),m_cdata(NULL),m_pdata(NULL),
  m_ofile("output.ppm")
{
  int x;

  //init things 0 jus in case
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
void rayp::argParse(string a)
{
  if (m_mode==10)
    {
      pparse(a);
      return;
    }
  
  if (m_mode==11)
    {      
      cparse(a);      
      return;
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

  if (a=="p")
    {
      m_mode=10;
      m_mc=0;
      return;
    }

  if (a=="s")
    {
      m_mode=11;
      m_mc=0;
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
}

//tmode=type mode (0=float)
//mmode=mode mode, same usage as m_mode
//msize=mode size, size of array to be filled
void rayp::arrayParse(int mmode,string a)
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
int rayp::arrayParseFill(int mmode,string a)
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

void rayp::printd()
{
  printf("b %f %f %f\n",m_background[0],m_background[1],m_background[2]);
  printf("from %f %f %f\n",m_from[0],m_from[1],m_from[2]);
  printf("at %f %f %f\n",m_at[0],m_at[1],m_at[2]);
  printf("up %f %f %f\n",m_up[0],m_up[1],m_up[2]);
  printf("angle %i\n",m_angle);
  printf("hither %i\n",m_hither);
  printf("res %i %i\n",m_res[0],m_res[1]);
  printf("fill %f %f %f %f %f %f %f %f\n",m_fill[0],m_fill[1],m_fill[2],m_fill[3],m_fill[4],m_fill[5],m_fill[6],m_fill[7]);
}

void rayp::printc()
{
  flink2<float*>* t=m_cdata;
  while (1)
    {
      if (!t)
        {
          return;
        }

      cout<<"c ";
      for (int x=0;x<4;x++)
        {          
          printf("%f ",t->m_data[x]);
        }

      cout<<endl;
      t=t->m_next;      
    }
}

void rayp::loadFile(string filename)
{
  fstream infile;
  infile.open(filename.c_str());

  string a;

  while(infile>>a)
  {
    argParse(a);
  }
}

void rayp::loadFile(string filename,string ofile)
{
  loadFile(filename);
  m_ofile=ofile;
}

//parse circles
void rayp::cparse(string &a)
{
  if (m_mc==0)
    {
      m_tc=new float[4];          
    }
      
  m_tc[m_mc]=atof(a.c_str());
  m_mc++;

  if (m_mc>3)
    {
      m_mc=0;
      m_mode=0;

      flink2<float*>* newf=new flink2<float*>(m_tc);
      newf->m_next=m_cdata;
      m_cdata=newf;
      m_tc=NULL;
    }
}

void rayp::pparse(string &a)
{
  //right after seeing a p command
  if (m_mc==0)
    {
      m_pc=atoi(a.c_str()); //store number as number of vertices
      m_tpg=new float*[m_pc];
      m_pctr=0; //reset counters
      m_pctr2=0;
      m_mc++;
      return;
    }

  //pctr 2 goes to 0 to 2 for xyz of point
  //makes new point at 0
  if (m_pctr2==0)
    {
      m_tpg[m_pctr]=new float[3];
    }

  //setting x y or z
  m_tpg[m_pctr][m_pctr2]=atof(a.c_str());
  
  m_pctr2++;

  //moving on to next point
  if (m_pctr2>2)
    {
      m_pctr2=0;
      m_pctr++;

      //if greater than 3rd point, start splitting
      //up triangles
      if (m_pctr>=3)
        {
          m_tpg2=new float*[3];
          m_tpg2[0]=m_tpg[0];
          m_tpg2[1]=m_tpg[m_pctr-2];
          m_tpg2[2]=m_tpg[m_pctr-1];

          //adding to linked list of triangles
          flink2<float**>* t=new flink2<float**>(m_tpg2);
          t->m_next=m_pdata;
          m_pdata=t;      
        }      
    }

  //reached max vertex count
  if (m_pctr>=m_pc)
    {
      m_mode=0;
    }
}

//print triangle data
void rayp::printt()
{
  flink2<float**>* t=m_pdata;
  cout<<"triangles:"<<endl;
  while (1)
    {
      if (!t)
        {
          return;
        }

      for (int x=0;x<3;x++)
        {          
          printf("%f %f %f\n",t->m_data[x][0],t->m_data[x][1],t->m_data[x][2]);          
        }

      cout<<endl;

      t=t->m_next;
    }
}
