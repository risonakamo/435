#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../common/slVector.H"
#include "io.H"
#include "sVtex.h"

using namespace std;

void writefile(vector<sVtex> &pts2,vector<SlTri> &tri);

int main()
{
  float lamb=1;
  float dt=1;
  int iter=1;
  
  vector<SlVector3> pts;
  vector<SlTri> tri;

  vector<sVtex> pts2;
  
  readObjFile("tests/a.obj",pts,tri);

  for (int x=0;x<pts.size();x++)
    {
      pts2.push_back(sVtex(pts[x]));
    }

  for (int x=0;x<pts.size();x++)
    {
      pts2[x].printP();
    }
  
  for (int y=0;y<iter;y++)
    {
      for (int x=0;x<tri.size();x++)
        {
          pts2[tri[x][0]].umbrella(pts2[tri[x][1]],pts2[tri[x][2]]);
        }
  
      for (int x=0;x<pts2.size();x++)
        {
          pts2[x].update(lamb,dt);
        }

      for (int x=0;x<pts.size();x++)
        {
          pts2[x].printP();
        }
    }

  writefile(pts2,tri);
  
  return 0;
}

void writefile(vector<sVtex> &pts2,vector<SlTri> &tri)
{
  ofstream outfile;
  outfile.open("output.obj");

  for (int x=0;x<pts2.size();x++)
    {
      outfile<<"v "<<(*(pts2[x].m_pt))[0]<<" "<<(*(pts2[x].m_pt))[1]<<" "<<(*(pts2[x].m_pt))[2]<<"\n";
    }

  for (int x=0;x<tri.size();x++)
    {
      
      outfile<<"f "<<tri[x][0]<<" "<<tri[x][1]<<" "<<tri[x][2]<<"\n";
    }

  outfile.close();
}
