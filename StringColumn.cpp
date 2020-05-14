#include "StringColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

 void StringColumn::copyFrom(const StringColumn& other)
 { 
    m_colname=new char[strlen(other.m_colname)+1];
   strcpy(m_colname, other.m_colname);
   m_stringcolumn=other.m_stringcolumn;
 }

StringColumn::StringColumn(const char* colname)
{
   m_colname= new char[strlen(colname)+1];
   strcpy(m_colname, colname);
   List<int>();
   cout<<"StringColumn constructor called"<<endl;
}

StringColumn::StringColumn(const StringColumn& other)
{
   copyFrom(other);
   cout<<"StringColumn copy constructor called"<<endl;
}

StringColumn& StringColumn::operator=(const StringColumn& other)
{
    if(this!=&other){
        delete[] m_colname;
        copyFrom(other);
    }
    cout<<"StringColumn operator== called"<<endl;
    return *this;
}

const char* StringColumn::getNameColumn()
{
   return m_colname;
}

const char* StringColumn::getType(){
    return "string";
}

void StringColumn::addElement(String value)
{
    m_stringcolumn.addElement(value);
}

void StringColumn::updateElement(int index, String value)
{
    m_stringcolumn[index]=value;
}

void StringColumn::printColumn()
{
   int size= m_stringcolumn.getSize();
   for(int i=0; i<size; i++)
   {
       cout<<m_stringcolumn[i]<<'\n'; 
   }
}