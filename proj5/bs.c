#include "bs.h"

bs::bs()
:t_bmode(0),t_force(0,0,0),t_fmode(0),m_currFood(0)
{
  
}

bs::bs(const string filename,const string outfile)
:t_bmode(0),t_force(0,0,0),t_fmode(0),m_currFood(0)
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

  m_numBirds=int(m_pars[11]);
  for (int x=0;x<m_numBirds*2;x++)
  {
    infile>>a;
    parseBoid(a);
  }

  infile>>a;
  m_numFood=atoi(a.c_str());

  for (int x=0;x<m_numFood*3;x++)
  {
    infile>>a;
    parseFood(a);
  }

  // while (infile>>a)
  // {
  //   parseBoid(a);
  // }

  calc();

  m_f=fopen(outfile.c_str(),"w");
  fprintf(m_f,"%i\n",m_frames);
}

void bs::calc()
{
  m_frames=int(m_pars[10])*30;
  m_maxNbour=int(m_pars[2]);
  m_tree=new KDTree(m_points);
  m_ftree=new KDTree(m_foods);
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

void bs::parseFood(string &fstring)
{  
  vector<SlVector3>* fvec;
  if (t_fmode==0)
  {
    fvec=&m_foods;
    t_fmode++;
  }

  else if (t_fmode==1)
  {
    fvec=&m_foodVel;
    t_fmode++;
  }

  else
  {
    t_fmode=0;

    m_foodT.push_back(atoi(fstring.c_str()));
    return;
  }

  stringstream stream(fstring);
  string a;
  SlVector3 newvec;
  int bcount=0;

  while (getline(stream,a,','))
  {
    if (bcount==0)
    {
      newvec[0]=atof(a.erase(0,1).c_str());
    }

    if (bcount==1)
    {
      newvec[1]=atof(a.c_str());
    }

    if (bcount==2)
    {
      newvec[2]=atof(a.erase(a.size()-1,1).c_str());
    }

    bcount++;
  }

  fvec->push_back(newvec);
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
        }

      if (bcount==1)
        {
          newvec[1]=atof(a.c_str());
        }

      if (bcount==2)
        {
          newvec[2]=atof(a.erase(a.size()-1,1).c_str());
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

  cout<<"foods"<<endl;
  for (int x=0;x<m_foods.size();x++)
  {
    cout<<m_foods[x]<<" "<<m_foodVel[x]<<" "<<m_foodT[x]<<endl;
  }
}

void bs::boutput()
{
  fprintf(m_f,"%i\n",m_numBirds);
  for (int x=0;x<m_points.size();x++)
  {
    fprintf(m_f,"[%f,%f,%f][%f,%f,%f]\n",m_points[x][0],m_points[x][1],m_points[x][2],
                                         m_vels[x][0],m_vels[x][1],m_vels[x][2]);
  }

  fprintf(m_f,"%i\n",m_currFood);
  for (int x=0;x<m_numFood;x++)
  {
    if (m_foodT[x]==-1)
    {
      fprintf(m_f,"[%f,%f,%f]\n",m_foods[x][0],m_foods[x][1],m_foods[x][2]);
    }
  }
}

void bs::run()
{
  int s=-1;
  for (int x=0;x<m_frames;x++)
  {
    if (x%30==0)
    {
      s++;
    }

    //for all birds
    for (int y=0;y<m_numBirds;y++)
    {
      t_force[0]=0;
      t_force[1]=0;
      t_force[2]=0;

      vector<int> nbours;
      m_tree->neighbors(m_points,m_points[y],m_maxNbour,m_pars[1],nbours);

      if (nbours.size()!=0)
      {
        centreForce(m_points[y],nbours,y);
        matchVel(m_points[y],nbours,y);
        colliForce(m_points[y],nbours,y);
        foodForce(m_points[y]);

        m_vels[y]+=(t_force*(m_pars[9]/m_pars[3]));
      }
      
      m_vels[y]*=m_pars[8];

      m_points[y]+=m_vels[y]*m_pars[9];

      boundCheck(m_points[y],m_vels[y]);
    }

    //for all foods check if some become active
    for (int y=0;y<m_foods.size();y++)
    {
      if (m_foodT[y]==s)
      {
        m_foodT[y]=-1;
        m_currFood++;
      }

      if (m_foodT[y]==-1)
      {
        m_foods[y]+=m_foodVel[y]*m_pars[9];

        foodSnap(m_foods[y]);  
      }
    }

    // //for all active foods
    // for (int y=0;y<m_currFood;y++)
    // {
    //   m_foods[y]+=m_foodVel[y]*m_pars[9];

    //   foodSnap(m_foods[y]);
    // }

    boutput();
  }
}

void bs::foodSnap(SlVector3 &food)
{
  if (food[0]>.5)
  {
    food[0]=.5;
  }

  else if (food[0]<-.5)
  {
    food[0]=-.5;
  }

  if (food[1]>.25)
  {
    food[1]=.25;
  }

  else if (food[1]<-.25)
  {
    food[1]=-.25;
  }

  if (food[2]>.125)
  {
    food[2]=.125;
  }

  else if (food[2]<-.125)
  {
    food[2]=.125;
  }
}

void bs::colliForce(SlVector3 &point,vector<int> &nbours,int &iself)
{
  //t vec being used as centre point
  t_vec[0]=0;
  t_vec[1]=0;
  t_vec[2]=0;

  for (int x=0;x<nbours.size();x++)
  {
    if (nbours[x]==iself)
    {
      continue;
    }

      // cout<<pow(mag(point-m_points[nbours[x]]),3)<<endl;
    t_vec+=(point-m_points[nbours[x]])/pow(mag(point-m_points[nbours[x]]),3);
  }

  t_force+=t_vec*m_pars[4];
}

void bs::centreForce(SlVector3 &point,vector<int> &nbours,int &iself)
{
  //t vec being used as centre point
  t_vec[0]=0;
  t_vec[1]=0;
  t_vec[2]=0;

  for (int x=0;x<nbours.size();x++)
  {
    if (nbours[x]==iself)
    {
      continue;
    }

    t_vec+=m_points[nbours[x]];
  }

  t_vec/=nbours.size();

  t_force+=(t_vec-point)*m_pars[5];
}

void bs::matchVel(SlVector3 &point,vector<int> &nbours,int &iself)
{
  //t vec being used as neighbour velocity
  t_vec[0]=0;
  t_vec[1]=0;
  t_vec[2]=0;

  for (int x=0;x<nbours.size();x++)
  {
    if (nbours[x]==iself)
    {
      continue;
    }

    t_vec+=m_vels[nbours[x]];
  }

  t_vec/=nbours.size();
  t_force+=(t_vec-point)*m_pars[6];
}

void bs::boundCheck(SlVector3 &point,SlVector3 &vel)
{
  if (point[0]>.5)
  {
    vel[0]=-abs(vel[0]);
  }

  else if (point[0]<-.5)
  {
    vel[0]=abs(vel[0]);
  }

  if (point[1]>.25)
  {
    vel[1]=-abs(vel[1]);
  }

  else if (point[1]<-.25)
  {
    vel[1]=abs(vel[1]);
  }

  if (point[2]>.125)
  {
    vel[2]=-abs(vel[2]);
  }

  else if (point[2]<-.125)
  {
    vel[2]=abs(vel[2]);
  }
}

void bs::treeTest()
{
  vector<int> result;
  m_tree->neighbors(m_points,m_points[0],10,.00000001,result);

  for (int x=0;x<result.size();x++)
  {
    cout<<result[x]<<endl;
  }
}

void bs::foodForce(SlVector3 &point)
{
  t_vec[0]=0;
  t_vec[1]=0;
  t_vec[2]=0;

  vector<int> fbours;
  m_ftree->neighbors(m_foods,point,m_maxNbour,m_pars[1],fbours);

  for (int x=0;x<fbours.size();x++)
  {
    if (m_foodT[fbours[x]]==-1)
    {
      t_vec+=m_foods[fbours[x]]-point;
    }
  }

  t_force+=t_vec*m_pars[7];
}