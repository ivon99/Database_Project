#include "Database.hpp"
#include <cstring>
#include <iostream>
using namespace std;

Table& Database::getTable(const char* tablename) const
{
    cout<<"Im inside gettable"<<endl;
   int size_database = m_database.getSize();
   for(int i=0; i<size_database; i++)
   {
       if(isTable(tablename))
       {
           cout<<"Succesfully will return table!"<<endl;
           return *m_database[i];
       }
   }
   cout<<"Unable to find a table with this tablename"<<endl;
   tablename--;
   return *m_database[0];
}

bool Database::isTable(char* tablename) const
{
    int size = m_database.getSize();
   for(int i=0;i<size;i++)
   {
       const char *this_name= m_database.getElement(i)->getName();
        /* int size_this_table = strlen(this_name);
       cout<<"Im gonna print it"<<endl;
       for(int i=0;i<size_this_table;i++)
       {
           cout<<(int)this_name[i]<<endl;
       }
       cout<<this_name<<endl; */
       cout<<"Comparison between" <<this_name<<"with strlen"<<strlen(this_name)<<" and"<<tablename<<"with stren"<<strlen(tablename)<<endl;
       if(strcmp(this_name, tablename)==0)
        {cout<<"Found match!"<<endl;
         return true;}
   }
   return false;
}

bool Database::isTable(const char* tablename) const
{
    int size = m_database.getSize();
   for(int i=0;i<size;i++)
   {
       const char *this_name= m_database.getElement(i)->getName();
       /*int size_this_table = strlen(this_name);
       cout<<"Im gonna print it"<<endl;
       for(int i=0;i<size_this_table;i++)
       {
           cout<<(int)this_name[i];
       } */
       cout<<"Comparison between" <<this_name<<"with strlen"<<strlen(this_name)<<" and"<<tablename<<"with stren"<<strlen(tablename)<<endl;
       if(strcmp(this_name, tablename)==0)
        {
            cout<<"Found match!"<<endl;
            return true;
         }
   }
   return false;
}


void Database::addTable(Table* new_table)
{
  
  if(isTable(new_table->getName()))
  {
      cout<<"Tablename already exists!"<<endl;
      return;
  }
  else
  {
      //Table* ptr_new_table= new Table(tablename);
      m_database.addElement(new_table);
      cout<<"Table with name"<< new_table->getName()<< "succesfully added to database!"<<endl; 
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

Table& Database::innerJoin(const char* tablename1,int col_index,const char* tablename2,int other_col_index)
{
    bool correct_first =isTable(tablename1);
    bool correct_second =isTable(tablename2);
    cout<<correct_first<<" "<<correct_second<<endl;
    if((!correct_first)||(!correct_second))
    {
        cout<<"Invalid names for tables!"<<endl;
        Table* tmp= new Table();
        return *tmp;
    }
    else
    {
        cout<<"Im gonna innerjoing"<<endl;
      return getTable(tablename1).innerJoin(col_index,getTable(tablename2),other_col_index);
    }
}

 void saveDatabaseToFile(std::ofstream& outfile, Database& obj)
 {
     int size = obj.m_database.getSize();
     for(int i=0; i<size;i++)
     {
       outfile<<obj.m_database[i]->getName()<<endl;
     }
 }