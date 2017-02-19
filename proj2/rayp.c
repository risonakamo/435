/*rayp.c - ray parser
  khang ngo
  cmsc 435 proj 1
  includes rayp object and flink2.  rayp object handles
  nff file parsing to be passed onto the rayd which does
  the math work*/

#include "rayp.h"

using namespace std;

rayp::rayp()
:m_mode(0),m_mc(0),m_angle(0),m_hither(0),/*m_cdata(NULL),m_pdata(NULL),*/
  m_ofile("output.ppm"),m_adata(NULL),m_fill(NULL)
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
//usable on arrays with specific size and non infinite
int rayp::arrayParseFill(int mmode,string a)
{
  if (mmode==1)
    {
      m_background[m_mc]=atof(a.c_str());
      //return the max size of the array being filled
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
      if (m_mc==0)
        {
          m_fill=new float[8];
        }

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
}

/* //print all circle data */
/* void rayp::printc() */
/* { */
/*   flink2<float*>* t=m_cdata; */
/*   while (1) */
/*     { */
/*       if (!t) */
/*         { */
/*           return; */
/*         } */

/*       cout<<"c "; */
/*       for (int x=0;x<4;x++) */
/*         {           */
/*           printf("%f ",t->m_data[x]); */
/*         } */

/*       cout<<endl; */
/*       t=t->m_next;       */
/*     } */
/* } */

//load file and parse all commands
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

//also load output filename
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

  //adding to adata
  if (m_mc>3)
    {
      m_mc=0;
      m_mode=0;
      
      iobj* t=new iobj(1,m_tc,m_fill,m_adata);
      m_adata=t;
      m_tc=NULL;
    }
}

//parse polygons
//i think i made this kind of badly
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
          fanTriangle();
        }      
    }

  //reached max vertex count
  if (m_pctr>=m_pc)
    {
      m_mode=0;
    }
}

/* //print triangle data */
/* void rayp::printt() */
/* { */
/*   flink2<float**>* t=m_pdata; */
/*   cout<<"triangles:"<<endl; */
/*   while (1) */
/*     { */
/*       if (!t) */
/*         { */
/*           return; */
/*         } */

/*       for (int x=0;x<3;x++) */
/*         {           */
/*           printf("%f %f %f\n",t->m_data[x][0],t->m_data[x][1],t->m_data[x][2]);           */
/*         } */

/*       cout<<endl; */

/*       t=t->m_next; */
/*     } */
/* } */

void rayp::fanTriangle()
{
  m_tp=new float[9];
  m_tp[0]=m_tpg[0][0];
  m_tp[1]=m_tpg[0][1];
  m_tp[2]=m_tpg[0][2];
  
  m_tp[3]=m_tpg[m_pctr-2][0];
  m_tp[4]=m_tpg[m_pctr-2][1];
  m_tp[5]=m_tpg[m_pctr-2][2];
  
  m_tp[6]=m_tpg[m_pctr-1][0];
  m_tp[7]=m_tpg[m_pctr-1][1];
  m_tp[8]=m_tpg[m_pctr-1][2];

  //adding to linked list of triangles
  iobj* t=new iobj(2,m_tp,m_fill,m_adata);
  m_adata=t;
}