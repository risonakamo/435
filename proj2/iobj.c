#include "iobj.h"

iobj::iobj()
:m_type(0),m_data(NULL),m_colour(NULL),m_next(NULL)
{
  
}

iobj::iobj(int type,float* data,float* colour,iobj* next)
:m_type(type),m_data(data),m_colour(colour),m_next(next)
{

}
