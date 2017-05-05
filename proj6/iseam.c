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

  // bob.outputPixl();

  // bob.calcEnergy(0);

  for (int x=0;x<200;x++)
  {
    bob.calcEnergy(0);
    bob.seamTrace();
    bob.rebuildImg();


  }

  bob.outputPixl();

  return 0;
}