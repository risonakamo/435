#include <iostream>

#include "bs.h"

using namespace std;

int main(int argc,char* argv[])
{  
  bs bob("tests/simple.in","output.out");

  bob.printPars();
  bob.printVecs();

  bob.boutput();
}
