#include "Double.hpp"
#include <iostream>
using namespace std;

Double::Double()
{
    m_double =0.0;
    m_null = true;
}
Double::Double(double value)
{
    m_double = value;
    m_null = false;
}
bool Double::isNULL() const
{
    return m_null;
}

double Double::getValue() const
{
    return m_double;
}

//==operators redefinition
bool Double::operator==(Double &other)
{
    return m_double == other.m_double;
}
bool Double::operator>(Double &other)
{
    return m_double > other.m_double;
}
bool Double::operator<(Double &other)
{
    return m_double < other.m_double;
}

//==conversion operators
Double::operator double()
{
    return m_double;
}

std::ostream &operator<<(std::ostream &out, const Double &object)
{
    out << object.getValue();
    return out;
}