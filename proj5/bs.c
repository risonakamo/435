#include "bs.h"

bs::bs()
{
  
}

bs::bs(const string filename)
{
  loadFile(filename);
}

void bs::loadFile(const string filename)
{
  fstream infile;
  infile.open(filename.c_str());

  string a;

  while (infile>>a)
    {
      cout<<a<<endl;
    }
}
