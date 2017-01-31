#include <iostream>
#include <fstream>
#include <string>

#include "rayd.h"
#include "pogn.h"

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

  pogn* bob2=new pogn("3");
  bob2->load(-123.5);
  bob2->load("-.012924302");
  bob2->vprint();
  
  return 0;
}
