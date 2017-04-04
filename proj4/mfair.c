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
  
  readObjFile("tests/bunny.obj",pts,tri);

  for (int x=0;x<pts.size();x++)
    {
      pts2.push_back(sVtex(pts[x]));
    }

  /* for (int x=0;x<pts.size();x++) */
  /*   { */
  /*     pts2[x].printP(); */
  /*   } */
  
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

      /* for (int x=0;x<pts.size();x++) */
      /*   { */
      /*     pts2[x].printP(); */
      /*   } */
    }

  writefile(pts2,tri);
  
  return 0;
}

void writefile(vector<sVtex> &pts2,vector<SlTri> &tri)
{
  FILE* f=fopen("output.obj","wb");

  for (int x=0;x<pts2.size();x++)
    {
      fprintf(f,"v %f %f %f\n",(*(pts2[x].m_pt))[0],(*(pts2[x].m_pt))[1],(*(pts2[x].m_pt))[2]);
      /* outfile<<"v "<<(*(pts2[x].m_pt))[0]<<" "<<(*(pts2[x].m_pt))[1]<<" "<<(*(pts2[x].m_pt))[2]<<endl; */
    }

  for (int x=0;x<tri.size();x++)
    {
      fprintf(f,"f %i %i %i\n",tri[x][0],tri[x][1],tri[x][2]);
      /* outfile<<"f "<<tri[x][0]<<" "<<tri[x][1]<<" "<<tri[x][2]<<endl; */
    }

}
