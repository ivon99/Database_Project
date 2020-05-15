#include "StringColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

void StringColumn::copyFrom(const StringColumn &other)
{
    m_colname = new char[strlen(other.m_colname) + 1];
    strcpy(m_colname, other.m_colname);
    m_stringcolumn = other.m_stringcolumn;
}

//==THE BIG 4==
StringColumn::StringColumn(const char *colname)
{
    m_colname = new char[strlen(colname) + 1];
    strcpy(m_colname, colname);
    List<String*>();
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
const char *StringColumn::getNameColumn()
{
    return m_colname;
}

const char *StringColumn::getType()
{
    return "string";
}

void StringColumn::addElement(String* value)
{
    cout<<"Im inside add element string"<<endl;
    m_stringcolumn.addElement(value);
    cout<<"!!Ive added element to string column and now it has size "<<m_stringcolumn.getSize()<<endl;
}

void StringColumn::updateElement(int index, String* value)
{
    m_stringcolumn[index] = value;
}

void StringColumn::deleteElement(int index)
{
    m_stringcolumn.deleteElement(index);
}

void StringColumn::printColumn()
{
    int size = m_stringcolumn.getSize();
    for (int i = 0; i < size; i++)
    {
        cout << m_stringcolumn[i] << '\n';
    }
}