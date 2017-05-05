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

  bob.rotateImg();

  for (int x=0;x<300;x++)
  {
    bob.calcEnergy();
    bob.seamTrace();
    bob.rebuildImg();
  }

  bob.rotateImg();

  bob.outputPixl();

  return 0;
}