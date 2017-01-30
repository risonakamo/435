#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  cout<<"boop"<<endl;

  ifstream infile;
  infile.open("a.nff");

  string a;
  infile>>a;
  cout<<a<<endl;

  infile>>a;
  cout<<a<<endl;
  
  infile>>a;
  cout<<a<<endl;
  
  return 0;
}
