#include "DoubleColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void DoubleColumn::copyFrom(const DoubleColumn &other)
{
    m_colname = new char[strlen(other.m_colname) + 1];
    strcpy(m_colname, other.m_colname);
    m_doublecolumn = other.m_doublecolumn;
    m_max_row_width = other.m_max_row_width;
}

DoubleColumn::DoubleColumn(const char *colname)
{
    m_colname = new char[strlen(colname) + 1];
    strcpy(m_colname, colname);
    List<double>();
    m_max_row_width=0;
    cout << "DoubleColumn constructor called" << endl;
}

DoubleColumn::DoubleColumn(const DoubleColumn &other)
{
    copyFrom(other);
    cout << "DoubleColumn copy constructor called" << endl;
}

DoubleColumn &DoubleColumn::operator=(const DoubleColumn &other)
{
    if (this != &other)
    {
        delete[] m_colname;
        copyFrom(other);
    }
    cout << "DoubleColumn operator== called" << endl;
    return *this;
}
//==getters==
const char *DoubleColumn::getType() const
{
    return "double";
}

const char *DoubleColumn::getNameColumn() const
{
    return m_colname;
}

int DoubleColumn::getMaxRowWidth() const 
{
   return m_max_row_width;
}

int DoubleColumn::getSize() const
{
    return m_doublecolumn.getSize();
}

IValue *DoubleColumn::getElement(int index)
{
    return &m_doublecolumn[index];
}

void DoubleColumn::addNullElement()
{
    Double *new_null_double = new Double();
    m_doublecolumn.addElement(*new_null_double);
    cout << "Ive added a null int" << endl;
}

void DoubleColumn::addElement(IValue *value)
{
    Double *new_double = new Double(value->getDoubleValue());
    m_doublecolumn.addElement(*new_double);
    int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void DoubleColumn::updateElement(int index, IValue *value)
{
    Double *new_double = new Double(value->getDoubleValue());
    m_doublecolumn[index] = *new_double;
    int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void DoubleColumn::deleteElement(int index)
{
    m_doublecolumn.deleteElement(index);
}
