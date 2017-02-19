#ifndef iobj_h
#define iobj_h

using namespace std;

class iobj
{
 public:
  iobj();

  iobj(int type,float* data,float* colour);
  
  /*type of shape thing:
   0=undefined
   1=sphere
   2=triangle
   3=patch*/
  int m_type;
  float* m_data;
  float* m_colour;

 private:
  
};
