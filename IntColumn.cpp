#include "IntColumn.hpp"
#include <iostream>
#include <cstring>
using namespace std;

 void IntColumn::copyFrom(const IntColumn& other)
 { 
    m_colname=new char[strlen(other.m_colname)+1];
   strcpy(m_colname, other.m_colname);
   m_intcolumn=other.m_intcolumn;
 }

IntColumn::IntColumn(const char* colname)
{
   m_colname= new char[strlen(colname)+1];
   strcpy(m_colname, colname);
   List<int>();
   cout<<"IntColumn constructor called"<<endl;
}

IntColumn::IntColumn(const IntColumn& other)
{
   copyFrom(other);
   cout<<"IntColumn copy constructor called"<<endl;
}

IntColumn& IntColumn::operator=(const IntColumn& other)
{
    if(this!=&other){
        delete[] m_colname;
        copyFrom(other);
    }
    cout<<"IntColumn operator== called"<<endl;
    return *this;
}

const char* IntColumn::getNameColumn()
{
   return m_colname;
}

const char* IntColumn::getType(){
    return "int";
}

void IntColumn::addElement(int value)
{
    m_intcolumn.addElement(value);
}

void IntColumn::updateElement(int index,int value) 
{
    m_intcolumn[index]=value;
}

void IntColumn::deleteElement(int index)
{
    m_intcolumn.deleteElement(index);
}

void IntColumn::printColumn()
{
   int size= m_intcolumn.getSize();
   for(int i=0; i<size; i++)
   {
       cout<<m_intcolumn[i]<<'\n';
   }
}




