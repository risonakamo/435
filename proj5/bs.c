#include "bs.h"

bs::bs()
:t_bmode(0)
{
  
}

bs::bs(const string filename,const string outfile)
:t_bmode(0)
{
  loadFile(filename,outfile);
}

void bs::loadFile(const string filename,const string outfile)
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

    calc();

    m_f=fopen(outfile.c_str(),"w");
    fprintf(m_f,"%i\n",m_frames);
}

void bs::calc()
{
  m_frames=m_pars[10]*30;
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
  fprintf(m_f,"%i\n",int(m_pars[11]));

  for (int x=0;x<m_points.size();x++)
  {
    fprintf(m_f,"[%f,%f,%f][%f,%f,%f]\n",m_points[x][0],m_points[x][1],m_points[x][2],
                                         m_vels[x][0],m_vels[x][1],m_vels[x][2]);
  }

  fprintf(m_f,"0\n");
}

void bs::run()
{
  for (int x=0;x<m_frames;x++)
  {
    for (int y=0;y<int(m_pars[11]);y++)
    {
      m_points[y]+=m_vels[y];

      if (m_points[y][0]>.5 || m_points[y][0]<-.5)
      {
        m_vels[y][0]=-m_vels[y][0];
      }

      if (m_points[y][1]>.25 || m_points[y][1]<-.25)
      {
        m_vels[y][1]=-m_vels[y][1];
      }

      if (m_points[y][2]>.125 || m_points[y][2]<-.125)
      {
        m_vels[y][2]=-m_vels[y][2];
      }
    }

    boutput();
  }
}

void bs::treeTest()
{
  m_tree=new KDTree(m_points);

  vector<int> result;
  m_tree->neighbors(m_points,m_points[0],10,.00000001,result);

  for (int x=0;x<result.size();x++)
  {
    cout<<result[x]<<endl;
  }
}