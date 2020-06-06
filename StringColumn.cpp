#include "StringColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void StringColumn::copyFrom(const StringColumn &other)
{
    m_colname = new char[strlen(other.m_colname) + 1];
    strcpy(m_colname, other.m_colname);
    m_stringcolumn = other.m_stringcolumn;
    m_max_row_width=other.m_max_row_width;
}

//==THE BIG 4==
StringColumn::StringColumn(const char *colname)
{
    m_colname = new char[strlen(colname) + 1];
    strcpy(m_colname, colname);
    List<String*>();
    m_max_row_width= 0;
    cout << "StringColumn constructor called" << endl;
}

StringColumn::StringColumn(const StringColumn &other)
{
    copyFrom(other);
    cout << "StringColumn copy constructor called" << endl;
}

StringColumn &StringColumn::operator=(const StringColumn &other)
{
    if (this != &other)
    {
        delete[] m_colname;
        copyFrom(other);
    }
    cout << "StringColumn operator== called" << endl;
    return *this;
}

// ==getters==
//==getters==
const char *StringColumn::getType() const
{
    return "string";
}

const char *StringColumn::getNameColumn() const
{
    return m_colname;
}

int StringColumn::getMaxRowWidth() const 
{
   return m_max_row_width;
}

int StringColumn::getSize() const
{
    return m_stringcolumn.getSize();
}

IValue *StringColumn::getElement(int index)
{
    return m_stringcolumn[index];
}

void StringColumn::addNullElement()
{
    String* new_null_string = new String();
    m_stringcolumn.addElement(new_null_string);
    cout << "Ive added a null int" << endl;
}

void StringColumn::addElement(IValue *value)
{
    String *new_string = new String(value->getCharValue(),0);
    cout<<"Freaky freaky things!"<<endl;
    m_stringcolumn.addElement(new_string);
    int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void StringColumn::updateElement(int index, IValue *value)
{
    String *new_string = new String(value->getCharValue());
    m_stringcolumn[index] = new_string;
    int new_int_size = value->getNumofChar();
    if (new_int_size > m_max_row_width)
        m_max_row_width = new_int_size;
}

void StringColumn::deleteElement(int index)
{
    m_stringcolumn.deleteElement(index);
}