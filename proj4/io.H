/* file given by instructor (not mine to comment)*/

#ifndef IO_H
#define IO_H
#include <vector>
#include "../common/slVector.H"

class SlTri {
public:
  inline SlTri(int x, int y, int z) {indices[0] = x; indices[1] = y; indices[2] = z;};
  
  inline SlTri() {};

  inline void set(int x, int y, int z) {indices[0] = x; indices[1] = y; indices[2] = z;};
  
  inline int &operator[](const unsigned int &i) { return indices[i];};
  
  inline int operator[](const unsigned int &i) const { return indices[i];};

  inline SlTri &operator=(const SlTri &that);

  int indices[3];
};

inline SlTri &SlTri::operator=(const SlTri &that) {
  this->indices[0] = that.indices[0];
  this->indices[1] = that.indices[1];
  this->indices[2] = that.indices[2];
  return (*this);
};

bool readObjFile(char *fname, std::vector<SlVector3> &pts, std::vector<SlTri> &triangles);

void writeObjFile(char *fname, const std::vector<SlVector3> &meshPts, const std::vector<SlTri> &triangles);

#endif
