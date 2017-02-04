#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "rayd.h"
#include "pogn.h"
#include "../common/slVector.H"

using namespace std;

int main()
{
  /* rayd* bob=new rayd; */

  /* bob->argParse("b"); */
  /* bob->argParse("1"); */
  /* bob->argParse(".132"); */
  /* bob->argParse("3"); */

  /* bob->argParse("angle"); */
  /* bob->argParse("32"); */

  /* bob->argParse("resolution"); */
  /* bob->argParse("512"); */
  /* bob->argParse("50000.2"); */

  /* bob->printd(); */

  /* pogn* succ=new pogn("3"); */
  /* succ->load(-123.5); */
  /* succ->load("-.012924302"); */
  /* succ->vprint(); */

  /* printf("\n"); */
  /* SlVector3* bill=new SlVector3(1,2,3); */
  /* cout<<(*bill)<<endl; */

  /* normalize(*bill); */
  /* cout<<*bill<<endl; */

  SlVector3 from(1,0,0);
  SlVector3 at(0,0,0);
  SlVector3 up(0,0,1);
  int angle=90;
  int dim=3; //number of side pixels
  
  SlVector3 w=from-at;
  SlVector3 u=cross(up,w);
  SlVector3 v=cross(w,u);

  float d=mag(from-at);
  float m=tan(angle*(3.14/180)*.5)*d;
  
  normalize(w);
  normalize(u);
  normalize(v);
  
  cout<<w<<endl;
  cout<<u<<endl;
  cout<<v<<endl;
  cout<<d<<endl;
  cout<<m<<endl;

  
  float* r;
  float** ppoints;
  int x=0;
  int y=0;  
  for (int z=0;z<pow(dim,2);z++)
    {
      r=new float[2];
      r[0]=-m+(x*((2*m)/dim))+(m/dim);
      r[1]=-m+(y*((2*m)/dim))+(m/dim);

      x++;
      if (x>=dim)
        {
          x=0;
          y++;
        }

      cout<<r[0]<<" "<<r[1]<<endl;
    }

  
  return 0;
}
