#include <iostream>

#include "bs.h"

using namespace std;

int main(int argc,char* argv[])
{  
  bs bob("tests/simple2","output");

  bob.printPars();
  // bob.printVecs();

  bob.run();
  // bob.treeTest();
}