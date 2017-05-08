#include "seam.h"

using namespace std;

int main(int argc,char* argv[])
{
  if (argc<5)
  {
    cout<<"seam <input file> <output file> <new width> <new height>"<<endl;
    return 0;
  }

  seam bob(argv[1]);

  bob.resize(atoi(argv[3]),atoi(argv[4]),argv[2]);

  return 0;
}