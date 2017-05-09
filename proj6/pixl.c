#include "pixl.h"

pixl::pixl()
:m_lab(0,0,0),m_parent(-1),m_energy(-1)
{

}

pixl::pixl(double l,double a,double b,int index)
:m_lab(l,a,b),m_parent(-1),m_energy(-1),m_index(index)
{
    
}