#include "bs.h"

bs::bs()
:t_bmode(0)
{
  
}

bs::bs(const string filename)
:t_bmode(0)
{
  loadFile(filename);
}

void bs::loadFile(const string filename)
{
  fstream infile;
  infile.open(filename.c_str());

  string a;

  for (int x=0;x<12;x++)
    {
      infile>>a;
      m_pars[x]=atof(a.c_str());
    }

  while (infile>>a)
    {
      parseBoid(a);
    }
}

void bs::printPars()
{
  cout<<"pars"<<endl;
  for (int x=0;x<12;x++)
    {
      cout<<m_pars[x]<<" ";
    }
  cout<<endl;
}

//bstring boidstring
void bs::parseBoid(string bstring)
{
  stringstream stream(bstring);
  string a;
  int bcount=0;

  vector<SlVector3>* bvec; //boid vec (points or vels)
  SlVector3 newvec;

  //boid mode (point or vel)
  if (t_bmode==0)
    {
      bvec=&m_points;
      t_bmode=1;
    }

  else
    {
      bvec=&m_vels;
      t_bmode=0;
    }
  
  while (getline(stream,a,','))
    {
      if (bcount==0)
        {
          newvec[0]=atof(a.erase(0,1).c_str());
          
          /* cout<<a.erase(0,1)<<endl; */
        }

      if (bcount==1)
        {
          newvec[1]=atof(a.c_str());
          
          /* cout<<a<<endl; */
        }

      if (bcount==2)
        {
          newvec[2]=atof(a.erase(a.size()-1,1).c_str());
          
          /* cout<<a.erase(a.size()-1,1)<<endl; */
        }

      bcount++;
    }

  bvec->push_back(newvec);
}

void bs::printVecs()
{
  cout<<"points:"<<endl;
  for (int x=0;x<m_points.size();x++)
    {
      cout<<m_points[x]<<endl;
    }

  cout<<"vels:"<<endl;
  for (int x=0;x<m_points.size();x++)
    {
      cout<<m_vels[x]<<endl;
    }
}

void bs::boutput()
{
  
}
