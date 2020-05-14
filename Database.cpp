#include "Database.hpp"
#include <cstring>
#include <iostream>
using namespace std;

bool Database::isTable(const char* tablename) const
{
    int size = m_database.getSize();
   for(int i=0;i<size;i++)
   {
       if(strcmp(m_database.getElement(i)->getName(), tablename)==0)
         return true;
   }
   return false;
}

void Database::addTable(const char* tablename)
{
  if(isTable(tablename))
  {
      cout<<"Tablename already exists!"<<endl;
      return;
  }
  else
  {
      Table* ptr_new_table= new Table(tablename);
      m_database.addElement(ptr_new_table);
      cout<<"Table with name"<< tablename<< "succesfully added to database!"<<endl; 
      return ;
  }
}

void Database::showtables() const 
{
    int size= m_database.getSize();
    for(int i=0; i<size;i++)
    {
        cout<<"Table #"<<i<<":"<<m_database.getElement(i)->getName()<<endl;
    }
}