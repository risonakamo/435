#include "pixl.h"

pixl::pixl()
:m_lab(0,0,0),m_parent(-1),m_energy(-1)
{

}

pixl::pixl(double l,double a,double b,int x,int y,int index)
:m_lab(l,a,b),m_parent(-1),m_energy(-1),m_index(index)
{
    m_pos[0]=x;
    m_pos[1]=y;
}