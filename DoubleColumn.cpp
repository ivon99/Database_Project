#include "DoubleColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

 void DoubleColumn::copyFrom(const DoubleColumn& other)
 { 
   m_colname=new char[strlen(other.m_colname)+1];
   strcpy(m_colname, other.m_colname);
   m_doublecolumn=other.m_doublecolumn;
 }

DoubleColumn::DoubleColumn(const char* colname)
{
   m_colname= new char[strlen(colname)+1];
   strcpy(m_colname, colname);
   List<int>();
   cout<<"DoubleColumn constructor called"<<endl;
}

DoubleColumn::DoubleColumn(const DoubleColumn& other)
{
   copyFrom(other);
   cout<<"DoubleColumn copy constructor called"<<endl;
}

DoubleColumn& DoubleColumn::operator=(const DoubleColumn& other)
{
    if(this!=&other){
        delete[] m_colname;
        copyFrom(other);
    }
    cout<<"DoubleColumn operator== called"<<endl;
    return *this;
}

const char* DoubleColumn::getNameColumn()
{
   return m_colname;
}

const char* DoubleColumn::getType(){
    return "double";
}

void DoubleColumn::addElement(double value)
{
    m_doublecolumn.addElement(value);
}

void DoubleColumn::printColumn()
{
   int size= m_doublecolumn.getSize();
   for(int i=0; i<size; i++)
   {
       cout<<m_doublecolumn[i]<<'\n';
   }
}
