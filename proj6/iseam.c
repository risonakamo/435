#include "seam.h"

using namespace std;

int main(int argc,char* argv[])
{
  if (argc<2)
  {
    cout<<"invalid inputs"<<endl;
    return 0;
  }

  seam bob(argv[1]);

  bob.calcEnergy(0);

  bob.printEnergy();

  bob.seamTrace();

  // bob.outputgrey();

  return 0;
}