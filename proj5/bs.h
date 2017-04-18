//bs boid system

#ifndef BS_H
#define BS_H

#include <iostream>
#include <fstream>
#include <string>

#include "../common/slVector.H"

using namespace std;

class bs
{
 public:
  bs();
  bs(const string filename);
  
  void loadFile(const string filename);
 private:
};

#endif
