#include "IntColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void IntColumn::copyFrom(const IntColumn &other)
{
    m_colname = new char[strlen(other.m_colname) + 1];
    strcpy(m_colname, other.m_colname);
    m_intcolumn = other.m_intcolumn;
    m_max_row_width = other.m_max_row_width;
}

//===THE BIG 4===
IntColumn::IntColumn(const char *colname, int rows)
{
    m_colname = new char[strlen(colname) + 1];
    strcpy(m_colname, colname);
    m_intcolumn = List<Int>();
    if (rows != 0)
    {
        for (int i = 0; i < rows; i++)
        {
            Int *new_int = new Int();
            m_intcolumn.addElement(*new_int);
        }
    }

    m_max_row_width = strlen(colname);
   // cout << "IntColumn constructor called" << endl;
}

IntColumn::IntColumn(const IntColumn &other)
{
    copyFrom(other);
    //cout << "IntColumn copy constructor called" << endl;
}

IntColumn &IntColumn::operator=(const IntColumn &other)
{
    if (this != &other)
    {
        delete[] m_colname;
        copyFrom(other);
    }
    //cout << "IntColumn operator== called" << endl;
    return *this;
}
//===getters==
const char *IntColumn::getType() const
{
    return "int";
}

const char *IntColumn::getNameColumn() const
{
    return m_colname;
}

int IntColumn::getMaxRowWidth() const
{
    return m_max_row_width;
}

int IntColumn::getSize() const
{
    return m_intcolumn.getSize();
}

IValue *IntColumn::getElement(int index)
{
    return &m_intcolumn[index];
}

void IntColumn::addNullElement()
{
    Int *new_null_int = new Int();
    m_intcolumn.addElement(*new_null_int);
    if (strlen("NULL") > m_max_row_width)
    {
        m_max_row_width = strlen("NULL");
    }
}

void IntColumn::addElement(IValue *value)
{
    Int *new_int = new Int(value->getIntValue());
    m_intcolumn.addElement(*new_int);
    unsigned int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void IntColumn::updateElement(int index, IValue *value)
{
    Int *new_int = new Int(value->getIntValue());
    m_intcolumn[index] = *new_int;
    unsigned int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void IntColumn::deleteElement(int index)
{
    m_intcolumn.deleteElement(index);
}
