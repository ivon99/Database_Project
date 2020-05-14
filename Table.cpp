#include "Table.hpp"
#include "IColumn.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;


//TODO: compare for double (aggregate for double)

//==HELPER FUNCTIONS==
/*
void Table::createColByType(const char* type, const char* colename)
{
  if(strcmp(type,"int")==0)
  {
     IntColumn(colname);
  }
  if(strcmp(type,"double")==0)
  {
   DoubleColumn(colname); 
  }
  if(strcmp(type,"string")==0)
  {
    StringColumn(colname);
  }
  else
  {
   cout<<"Invalid column type!"<<endl;
  }
}
*/

// ==THE BIG 4===
Table::Table(const char *name)
{
  m_tablename = new char[strlen(name) + 1];
  m_table = List<IColumn *>();
}

Table::Table(const Table &other)
{
  m_tablename = new char[strlen(other.m_tablename) + 1];
  strcpy(m_tablename, other.m_tablename);
  m_table = other.m_table;
}

Table &Table::operator=(const Table &other)
{
  if (this != &other)
  {
    delete[] m_tablename;
    m_tablename = new char[strlen(other.m_tablename) + 1];
    strcpy(m_tablename, other.m_tablename);
    m_table = other.m_table;
  }
  return *this;
}

Table::~Table()
{
  int num_col = m_table.getSize();
  for (int i = 0; i < num_col; i++)
  {
    delete m_table[i];
  }
}

//===GETTERS AND PRINTERS===
void Table::describe() const
{
  int num_columns = m_table.getSize();
  for (int i = 0; i < num_columns; i++)
  {
    std::cout << "Column #" << i << ": " << m_table[i]->getNameColumn() << " is of type " << m_table[i]->getType() << "." << endl;
  }
}

const char *Table::getName() const
{
  return m_tablename;
}

/*
void Table::print() const
{
  ;
} */
int Table::count(int col_index, int value) const
{
  int col_size= m_table.getElement(col_index)->getSize();
  int ctr=0;
  for(int i=0;i<col_size; i++)
  {
    if(m_table.getElement(col_index)->getIntElement(i)==value) 
     ctr++;
  }
   cout<<"Ctr is "<<ctr<<endl;
  return ctr;
}

int Table::count(int col_index, double value) const
{
  int col_size= m_table.getElement(col_index)->getSize();
  int ctr=0;
  for(int i=0; i<col_size; i++)
  {
    if(m_table.getElement(col_index)->getDoubleElement(i)==value) 
     ctr++;
  }
  cout<<"Ctr is "<<ctr<<endl;
   return ctr;
}

int Table::count(int col_index, const char* value) const
{
  int col_size= m_table.getElement(col_index)->getSize();
  int ctr=0;
  for(int i=0; i<col_size; i++)
  {
    if(strcmp(m_table.getElement(col_index)->getStringElement(i),value)==0) 
     ctr++;
  }
   cout<<"Ctr is "<<ctr<<endl;
  return ctr;
}

//===TABLE METHODS===
bool Table::addColumn(const char *colname, const char *type)
{
  IColumn *col;
  if (strcmp(type, "string") == 0)
  {
    col = new StringColumn(colname);
    m_table.addElement(col);
    std::cout << "String column to be added?" << endl;
    return true;
  }
  if (strcmp(type, "int") == 0)
  {
    col = new IntColumn(colname);
    m_table.addElement(col);
    std::cout << "Int column to be added?" << endl;
    return true;
  }
  if (strcmp(type, "double") == 0)
  {
    col = new DoubleColumn(colname);
    m_table.addElement(col);
    std::cout << "Double column to be added?" << endl;
    return true;
  }
  else
  {
    std::cout << "Invalid type for new column." << std::endl;
    return false;
  }
}

void Table::insertIntValue(int value, int col_index)
{
  m_table[col_index]->addElement(value);
}

void Table::insertDoubleValue(double value, int col_index)
{

  m_table[col_index]->addElement(value);
}

void Table::insertStringValue(String value, int col_index)
{

  m_table[col_index]->addElement(value);
}

//TODO: NULL!!!
void Table::insertRow(int col_index)
{
  const char *type = new char[7];
  type = m_table[col_index]->getType();
  if (strcmp(type, "int") == 0)
  {
    insertIntValue(0, col_index);
  }
  if (strcmp(type, "double") == 0)
  {
    insertDoubleValue(0.0, col_index);
  }
  if (strcmp(type, "string") == 0)
  {
    insertStringValue("NULL", col_index);
  }
}

void Table::select(int col_index, int value)
{
  int size_col = m_table.getElement(col_index)->getSize();
  int num_col = m_table.getSize();
  const char *type = new char[7];
  for (int i = 0; i < size_col; i++)
  {
    if (m_table.getElement(col_index)->getIntElement(i) == value)
    {
      for (int j = 0; j < num_col; j++)
      {
        type = m_table.getElement(j)->getType();
        if (strcmp(type, "int") == 0)
        {
          std::cout << m_table.getElement(j)->getIntElement(i) << " ";
        }
        if (strcmp(type, "double") == 0)
        {
          std::cout << m_table.getElement(j)->getDoubleElement(i) << " ";
        }
        if (strcmp(type, "string") == 0)
        {
          std::cout << m_table.getElement(j)->getStringElement(i) << " ";
        }
      }
      std::cout << endl;
    }
  }
}

void Table::select(int col_index, double value)
{
  int size_col = m_table.getElement(col_index)->getSize();
  int num_col = m_table.getSize();
  const char *type = new char[7];
  for (int i = 0; i < size_col; i++)
  {
    if (m_table.getElement(col_index)->getDoubleElement(i) == value)
    {
      for (int j = 0; j < num_col; j++)
      {
        type = m_table.getElement(j)->getType();
        if (strcmp(type, "int") == 0)
        {
          std::cout << m_table.getElement(j)->getIntElement(i) << " ";
        }
        if (strcmp(type, "double") == 0)
        {
          std::cout << m_table.getElement(j)->getDoubleElement(i) << " ";
        }
        if (strcmp(type, "string") == 0)
        {
          std::cout << m_table.getElement(j)->getStringElement(i) << " ";
        }
      }
      std::cout << endl;
    }
  }
}
//TODO: delete type, break it up into smaller functions
void Table::select(int col_index, const char *value)
{
  int size_col = m_table.getElement(col_index)->getSize();
  int num_col = m_table.getSize();
  const char *type = new char[7];
  for (int i = 0; i < size_col; i++)
  {
    if (strcmp(m_table.getElement(col_index)->getStringElement(i), value) == 0) //TODO: to be able to == string
    {
      for (int j = 0; j < num_col; j++)
      {
        type = m_table.getElement(j)->getType();
        if (strcmp(type, "int") == 0)
        {
          std::cout << m_table.getElement(j)->getIntElement(i) << " ";
        }
        if (strcmp(type, "double") == 0)
        {
          std::cout << m_table.getElement(j)->getDoubleElement(i) << " ";
        }
        if (strcmp(type, "string") == 0)
        {
          std::cout << m_table.getElement(j)->getStringElement(i) << " ";
        }
      }
      std::cout << endl;
    }
  }
}

void Table::updateRows(int search_col_index, int search_value, int target_col_index, int target_value)
{
  int size_search_col = m_table.getElement(search_col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    if (m_table.getElement(search_col_index)->getIntElement(i) == search_value)
    {
      m_table.getElement(target_col_index)->updateElement(i, target_value);
    }
  }
}

void Table::updateRows(int search_col_index, double search_value, int target_col_index, double target_value)
{
  int size_search_col = m_table.getElement(search_col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    if (m_table.getElement(search_col_index)->getDoubleElement(i) == search_value)
    {
      m_table.getElement(target_col_index)->updateElement(i, target_value);
    }
  }
}

void Table::updateRows(int search_col_index, String search_value, int target_col_index, const char *target_value)
{
  int size_search_col = m_table.getElement(search_col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    if (strcmp(m_table.getElement(search_col_index)->getStringElement(i), search_value.convertToChar()) == 0) //TOO: strcmp
    {
      String value_str(target_value);
      m_table.getElement(target_col_index)->updateElement(i, value_str);
    }
  }
}

void Table::deleteRows(int col_index, int value)
{
  int num_col = m_table.getSize();
  cout<<"Num col is"<<num_col<<endl;
  int size_search_col = m_table.getElement(col_index)->getSize();
  cout<<"Num rows is "<<size_search_col<<endl;
  for (int i =size_search_col-1; i >-1; i--)
  {
    cout<<"Int element is" << m_table.getElement(col_index)->getIntElement(i) <<endl;
    if (m_table.getElement(col_index)->getIntElement(i) == value)
    {
      for (int j = 0; j < num_col; j++)
      {
        cout<<"Im inside"<<endl;
        cout<<"For element in column "<<j<<" and will delete element "<< i<<endl;
        m_table.getElement(j)->deleteElement(i);
      }
    }
  }
}

void Table::deleteRows(int col_index, double value)
{
  int num_col = m_table.getSize();
  int size_search_col = m_table.getElement(col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    if (m_table.getElement(col_index)->getDoubleElement(i) == value)
    {
      for (int j = 0; i < num_col; j++)
      {
        m_table.getElement(j)->deleteElement(i);
      }
    }
  }
}

void Table::deleteRows(int col_index, String value)
{
  int num_col = m_table.getSize();
  int size_search_col = m_table.getElement(col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    String tmp(value);
    if (strcmp(m_table.getElement(col_index)->getStringElement(i),tmp.convertToChar())==0)
    {
      for (int j = 0; i < num_col; j++)
      {
        m_table.getElement(j)->deleteElement(i);
      }
    }
  }
}

void Table::aggregate(int col_index, int value, int target_col_index, const char* operation)
{
   int size_col = m_table.getElement(col_index)->getSize();
   for(int i=0; i<size_col;i++)
   {
     if(m_table.getElement(col_index)->getIntElement(i)==value)
     {
       if(strcmp(operation,"sum")==0)
       {
         int sum = m_table.getElement(col_index)->getIntElement(i) +  m_table.getElement(target_col_index)->getIntElement(i);
         cout<<"!!Sum is "<<sum<<endl;
          m_table.getElement(target_col_index)->updateElement(i,sum); 
          cout<<m_table.getElement(target_col_index)->getIntElement(i);
          continue;
       }
       if(strcmp(operation,"product")==0)
       {
         int product = m_table.getElement(col_index)->getIntElement(i) *  m_table.getElement(target_col_index)->getIntElement(i);
          cout<<"!!Product is "<<product<<endl;
          m_table.getElement(target_col_index)->updateElement(i,product);
          continue;
       }
       if(strcmp(operation, "maximum")==0)
       {
         cout<<"Inside maximum"<<endl;
         if(m_table.getElement(target_col_index)->getIntElement(i) < m_table.getElement(col_index)->getIntElement(i))
          m_table.getElement(target_col_index)->updateElement(i,m_table.getElement(col_index)->getIntElement(i));
         continue; 
       }  
       if(strcmp(operation,"minimum")==0)
       {
         cout<<"Inside minimum"<<endl;
        if(m_table.getElement(target_col_index)->getIntElement(i) >  m_table.getElement(col_index)->getIntElement(i))
          m_table.getElement(target_col_index)->updateElement(i,m_table.getElement(col_index)->getIntElement(i));
         continue; 
       }
     }
   }
}


/*
  void innerJoin()
  {
     ;
  }
   */

void Table::rename(const char *new_name)
{
  delete[] m_tablename;
  m_tablename = new char[strlen(new_name) + 1];
  stpcpy(m_tablename, new_name);
}

/*
  void Table:: exportTable(std::ofstream outfile)
  { 
     return ;
  } */

Table &readTableFromFile(std::ifstream &infile, Table &obj)
{
  std::cout << "Im inside importtable function" << endl;
  //==imports tablename==
  int tablename_size;
  infile >> tablename_size;
  char tablename[tablename_size];
  infile >> tablename;
  obj.m_tablename = new char[tablename_size];
  strcpy(obj.m_tablename, tablename);
  std::cout << "Succesfully read tablename " << obj.m_tablename << endl;

  //==imports dimensions of table==
  int num_rows;
  infile >> num_rows;
  int num_col;
  infile >> num_col;
  std::cout << "Dimensions of table are " << num_rows << "X" << num_col << endl;

  //==creates table with empty columns of the given types==
  char *type = new char[7];
  int colname_size;
  for (int i = 0; i < num_col; i++)
  {
    infile >> colname_size;
    char *colname = new char[colname_size];
    infile >> colname;
    infile >> type;
    std::cout << "To add column name of type" << colname << " t:" << type << endl;
    obj.addColumn(colname, type);
    std::cout << "Added column.Table now has:\n";
    obj.describe();
  }

  //==adds the values for the table==
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      const char *type = new char[7];
      type = obj.m_table[j]->getType();
      std::cout << "type is " << type << endl;

      if (strcmp(type, "int") == 0)
      {
        int value;
        infile >> value;
        std::cout << "[" << i << "][" << j << "] put int value" << value << endl;
        obj.insertIntValue(value, j);
      }
      if (strcmp(type, "double") == 0)
      {
        double value;
        infile >> value;
        std::cout << "[" << i << "][" << j << "] put double value" << value << endl;
        obj.insertDoubleValue(value, j);
      }
      if (strcmp(type, "string") == 0)
      {
        char *text = new char[100];
        infile >> text;
        std::cout << "[" << i << "][" << j << "] put string text " << text << endl;
        String *str_ptr = new String(text);
        std::cout << *str_ptr;
        // const char* value_in= str_ptr->convertToChar();
        //cout<<value_in;
        obj.insertStringValue(*str_ptr, j);
        std::cout << "im here!" << endl;
      }
    }
  }
  return obj;
}

void writeTableToFile(std::ofstream &outfile, Table &obj)
{
  std::cout << "Im inside writeTabletoFile function" << endl;
  //==writes tablename==
  int tablename_size = strlen(obj.m_tablename);
  outfile << tablename_size << " ";
  outfile << obj.m_tablename << endl;
  std::cout << "Succesfully wrote tablename" << endl;

  //==writes dimensions of table==
  //TODO: to make sure i implement so every row adds a row to the whole table
  int num_rows = obj.m_table[1]->getSize();
  outfile << num_rows << " ";
  std::cout << obj.m_table[1]->getSize();
  int num_col = obj.m_table.getSize();
  outfile << num_col << endl;
  std::cout << "Dimensions of table are " << num_rows << "X" << num_col << endl;

  //==creates table with empty columns of the given types==
  const char *type = new char[7];
  int colname_size;
  for (int i = 0; i < num_col; i++)
  {
    colname_size = strlen(obj.m_table.getElement(i)->getNameColumn());
    outfile << colname_size << " ";
    outfile << obj.m_table.getElement(i)->getNameColumn() << " ";
    outfile << obj.m_table.getElement(i)->getType() << endl;
  }
  std::cout << "Wrote columns and their types" << endl;

  //==adds the values for the table==
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      type = obj.m_table.getElement(j)->getType();
      if (strcmp(type, "int") == 0)
      {
        int element = obj.m_table.getElement(j)->getIntElement(i);
        outfile << element << " ";
        std::cout << "[" << i << "][" << j << "] write int value" << endl;
        continue;
      }
      if (strcmp(type, "double") == 0)
      {
        double element = obj.m_table.getElement(j)->getDoubleElement(i);
        outfile << element << " ";
        std::cout << "[" << i << "][" << j << "] write double value" << endl;
        continue;
      }
      if (strcmp(type, "string") == 0)
      {
        //TODO: Make a conversion from string to const char
        const char *element = obj.m_table.getElement(j)->getStringElement(i);
        outfile << element << " ";
        std::cout << "[" << i << "][" << j << "] write strig value" << endl;
        continue;
      }
    }
    outfile << endl;
  }
}