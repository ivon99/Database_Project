#include "Double.hpp"
#include <iostream>
#include <cmath>
//! used to set comparison precision 
const double EPSILON = 0.00001;
//! used when setting how many digits after decimal point will be printed
int const DOUBLE_PRECISION=5;
using namespace std;

Double::Double()
{
    m_double = 0.0;
    m_null = true;
   // cout << "Im inside double constructor!" << endl;
}
Double::Double(double value)
{
    m_double = value;
    m_null = false;
    //cout << "Im inside double constructor with value" << m_double;
}

const char *Double::getType() const
{
    return "double";
}

int Double::getNumofChar() const
{
    double tmp_copy=m_double;
    int ctr = 0;
    if (tmp_copy< 0)  //if a negative double
    {
        ctr++;       //count the minus sign
        tmp_copy *= (-1);  //turn it to positive
    }
    int y = tmp_copy;
    while (y > 0)  //count how many digits before decimal point
    {
        y = y / 10;
        ctr++;
    } //sum them with decimal sign and num of digits after decimal point
    return ctr+DOUBLE_PRECISION+1; 
}

bool Double::isNULL() const
{
    return m_null;
}
//==getters
int Double::getIntValue() const
{
    return (int)m_double;
}

double Double::getDoubleValue() const
{
    return m_double;
}

const char *Double::getCharValue() const
{
    const char *to_char = new char;
    const char double_char = (char)(int)m_double;
    to_char = &double_char;
    return to_char;
}

//==operators redefinition
bool Double::is_equal(IValue *rhs) const
{
    double rhs_double = rhs->getDoubleValue();
    return abs(m_double - rhs_double) < EPSILON;
}

bool Double::is_bigger(IValue *rhs) const
{
    double rhs_double = rhs->getDoubleValue();
    return m_double > rhs_double;
}

bool Double::is_smaller(IValue *rhs) const
{
    double rhs_double = rhs->getDoubleValue();
    return m_double < rhs_double;
}

std::ostream &operator<<(std::ostream &out, const IValue *value)
{
    double double_value = value->getDoubleValue();
    out << double_value;
    return out;
}