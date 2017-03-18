/*ilit.c - intersection object
 khang ngo
 cmsc 435 proj2
 represents different types of objects used in intersecting,
 including spheres polygons and lights. stores data as 1d array
 and doubles as linked list*/

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
