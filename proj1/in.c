#include <iostream>
#include <fstream>
#include <string>

#include "rayd.h"
#include "pogn.h"
#include "../common/slVector.H"

using namespace std;

int main()
{
  rayd* bob=new rayd;

  bob->argParse("b");
  bob->argParse("1");
  bob->argParse(".132");
  bob->argParse("3");

  bob->argParse("angle");
  bob->argParse("32");

  bob->argParse("resolution");
  bob->argParse("512");
  bob->argParse("50000.2");

  bob->printd();

  pogn* succ=new pogn("3");
  succ->load(-123.5);
  succ->load("-.012924302");
  succ->vprint();

  printf("\n");
  SlVector3* bill=new SlVector3(1,2,3);
  cout<<*bill;
  
  return 0;
}
