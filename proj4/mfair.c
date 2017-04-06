#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../common/slVector.H"
#include "io.H"
#include "sVtex.h"

using namespace std;

void writefile(const char* filename,vector<sVtex> &pts2,vector<SlTri> &tri);

int main(int argc,char* argv[])
{
  if (argc!=6)
    {
      cout<<"missing some arguments"<<endl;
      cout<<"mfair <input obj> <output obj> <lambda> <dt> <iterations>"<<endl;
      return 0;
    }
  
  float lamb=atof(argv[3]);
  float dt=atof(argv[4]);
  int iter=atof(argv[5]);

  vector<SlVector3> pts;
  vector<SlTri> tri;
  vector<sVtex> pts2;
  
  readObjFile(argv[1],pts,tri);

  for (int x=0;x<pts.size();x++)
    {
      pts2.push_back(sVtex(pts[x]));
    }

  for (int y=0;y<iter;y++)
    {
      for (int x=0;x<tri.size();x++)
        {
          pts2[tri[x][0]].umbrella(pts2[tri[x][1]],pts2[tri[x][2]]);
          pts2[tri[x][1]].umbrella(pts2[tri[x][0]],pts2[tri[x][2]]);
          pts2[tri[x][2]].umbrella(pts2[tri[x][0]],pts2[tri[x][1]]);
        }
  
      for (int x=0;x<pts2.size();x++)
        {
          pts2[x].update(lamb,dt);
          pts2[x].reset();
        }
    }

  writefile(argv[2],pts2,tri);
  
  return 0;
}

void writefile(const char* filename,vector<sVtex> &pts2,vector<SlTri> &tri)
{
  FILE* f=fopen(filename,"wb");

  for (int x=0;x<pts2.size();x++)
    {
      fprintf(f,"v %f %f %f\n",(*(pts2[x].m_pt))[0],(*(pts2[x].m_pt))[1],(*(pts2[x].m_pt))[2]);
    }

  for (int x=0;x<tri.size();x++)
    {
      fprintf(f,"f %i %i %i\n",tri[x][0]+1,tri[x][1]+1,tri[x][2]+1);
    }

}
