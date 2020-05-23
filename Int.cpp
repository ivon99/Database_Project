#include "Int.hpp"
#include <iostream>
using namespace std;

Int::Int()
{
    m_int = 0;
    m_null = true;
}

Int::Int(int value)
{
    m_int = value;
    m_null = false;
}

bool Int::isNULL() const
{
    return m_null;
}

//==operators redefinition
bool Int::operator==(Int &other)
{
    return m_int == other.m_int;
}
bool Int::operator>(Int &other)
{
    return m_int > other.m_int;
}
bool Int::operator<(Int &other)
{
    return m_int < other.m_int;
}

//==conversion operators
Int::operator int()
{
    return m_int;
}

std::ostream &operator<<(std::ostream &out, const Int &object)
{
    out << object.m_int;
    return out;
}
