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
  if (argc!=2)
    {
      cout<<"missing argument"<<endl;
      return 0;
    }
  
  float lamb=1;
  float dt=1;
  int iter=50;

  vector<SlVector3> pts;
  vector<SlTri> tri;
  vector<sVtex> pts2;
  
  readObjFile(argv[1],pts,tri);

  for (int x=0;x<pts.size();x++)
    {
      pts2.push_back(sVtex(pts[x]));
    }

  /* for (int x=0;x<pts.size();x++) */
  /*   { */
  /*     pts2[x].printP(); */
  /*   } */

  /* //print triangles */
  /* for (int x=0;x<tri.size();x++) */
  /*   { */
  /*     printf("%i %i %i\n",tri[x][0],tri[x][1],tri[x][2]); */
  /*   } */
  
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

      // for (int x=0;x<pts2.size();x++)
      //   {
      //     pts2[x].printP();
      //   }
    }

  writefile("output.obj",pts2,tri);
  
  return 0;
}

void writefile(const char* filename,vector<sVtex> &pts2,vector<SlTri> &tri)
{
  FILE* f=fopen(filename,"wb");

  for (int x=0;x<pts2.size();x++)
    {
      fprintf(f,"v %f %f %f\n",(*(pts2[x].m_pt))[0],(*(pts2[x].m_pt))[1],(*(pts2[x].m_pt))[2]);
      /* outfile<<"v "<<(*(pts2[x].m_pt))[0]<<" "<<(*(pts2[x].m_pt))[1]<<" "<<(*(pts2[x].m_pt))[2]<<endl; */
    }

  for (int x=0;x<tri.size();x++)
    {
      fprintf(f,"f %i %i %i\n",tri[x][0]+1,tri[x][1]+1,tri[x][2]+1);
      /* outfile<<"f "<<tri[x][0]<<" "<<tri[x][1]<<" "<<tri[x][2]<<endl; */
    }

}
