/*ilit.c - intersection light rasteriser version
 khang ngo
 cmsc 435 proj3
 simplified version of the iobj. was seperated
 when the iobj got a lot more data members than a
 light would ever need, so they couldnt share data
 types anymore*/

#include "ilit.h"

//default constructor
ilit::ilit()
:m_type(4),m_data(NULL),m_colour(NULL),m_next(NULL)
{
  
}

//set stuff constructor
ilit::ilit(double* data,double* colour,ilit* next)
:m_type(4),m_data(data),m_colour(colour),m_next(next)
{
  
}
