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

const char *Int::getType() const
{
    return "int";
}

int Int::getNumofChar() const
{
    int tmp=m_int;
    int ctr = 0;
    if (tmp < 0)
        ctr++;
    while (tmp != 0)
    {
        tmp = tmp / 10;
        ctr++;
    }
    return ctr;
}

bool Int::isNULL() const
{
    return m_null;
}
//==getters
int Int::getIntValue() const
{
    return m_int;
}

double Int::getDoubleValue() const
{
    return (double)m_int;
}

const char *Int::getCharValue() const
{
    const char *to_char = new char;
    const char int_char = (char)m_int;
    to_char = &int_char;
    return to_char;
}

//==operators redefinition
bool Int::is_equal(IValue *rhs) const
{
    int rhs_int = rhs->getIntValue();
    return m_int == rhs_int;
}

bool Int::is_bigger(IValue *rhs) const
{
    int rhs_int = rhs->getIntValue();
    return m_int > rhs_int;
}

bool Int::is_smaller(IValue *rhs) const
{
    int rhs_int = rhs->getIntValue();
    return m_int < rhs_int;
}