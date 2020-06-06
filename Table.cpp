#include "Table.hpp"
#include "IColumn.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <sys/ioctl.h>
using namespace std;
const int MAX_NAMEFILE_SIZE = 100;
const int MAX_TABLENAME_SIZE = 1000;
const int MAX_COLNAME_SIZE = 1000;
const int MAX_STRING_ROW_SIZE = 100;
const unsigned int MAX_COLUMN_NAMES_SIZE = 1000000000;
//TODO:make interface
//TODO: make print function

//===helper functions input===
int convertTextToNum(char *text)
{
  int size = strlen(text);
  int initial_pos = 0;
  if ((text[0] == '-') || (text[0] == '+'))
    initial_pos = 1;
  int digit = 0;
  int out_int = 0;
  for (int i = initial_pos; i < size; i++)
  {
    cout << text[i] << endl;
    digit = text[i] - '0';
    out_int += digit * pow(10, size - i);
  }

  if (text[0] == '-')
    return -out_int / 10;

  return out_int / 10;
}

// ==THE BIG 4===
Table::Table(const char *name)
{
  m_filename = new char[MAX_NAMEFILE_SIZE];
  strcpy(m_filename, "nofile");
  m_tablename = new char[strlen(name) + 1];
  strcpy(m_tablename, name);
  m_table = List<IColumn *>();
}

Table::Table(const Table &other)
{
  cout << "Table copy constructor called" << endl;
  m_tablename = new char[strlen(other.m_tablename) + 1];
  strcpy(m_tablename, other.m_tablename);
  cout << "Now tablename is" << m_tablename;
  m_filename = new char[strlen(other.m_filename) + 1];
  strcpy(m_filename, other.m_filename);
  m_table = other.m_table;
}

Table &Table::operator=(const Table &other)
{
  cout << "Table operator = called" << endl;
  if (this != &other)
  {
    delete[] m_tablename;
    delete[] m_filename;
    m_tablename = new char[strlen(other.m_tablename) + 1];
    strcpy(m_tablename, other.m_tablename);
    cout << "Now tablename is " << m_tablename << endl;
    m_filename = new char[strlen(other.m_filename) + 1];
    strcpy(m_filename, other.m_filename);
    m_table = other.m_table;
  }
  return *this;
}

Table::~Table()
{
  delete[] m_filename;
  delete[] m_tablename;
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

char *Table::getName()
{
  return m_tablename;
}

char *Table::getFilename() const
{
  return m_filename;
}

void Table::setFilename(const char *filename)
{
  delete[] m_filename;
  m_filename = new char[strlen(filename) + 1];
  strcpy(m_filename, filename);
}

//==methods
bool Table::addColumn(const char *colname, const char *type)
{
  if (strcmp(type, "string") == 0)
  {
    IColumn *col = new StringColumn(colname);
    m_table.addElement(col);
    std::cout << "String column to be added." << endl;
    return true;
  }
  if (strcmp(type, "int") == 0)
  {
    IColumn *col = new IntColumn(colname);
    m_table.addElement(col);
    std::cout << "Int column to be added." << endl;
    return true;
  }
  if (strcmp(type, "double") == 0)
  {
    IColumn *col = new DoubleColumn(colname);
    m_table.addElement(col);
    std::cout << "Double column to be added." << endl;
    return true;
  }
  else
  {
    std::cout << "Invalid type for new column." << std::endl;
    return false;
  }
}

int Table::count(int col_index, IValue *value) const
{
  int col_size = m_table.getElement(col_index)->getSize();
  int ctr = 0;
  for (int i = 0; i < col_size; i++)
  {
    IValue *row_value = m_table.getElement(col_index)->getElement(i);
    if (row_value->is_equal(value))
      ctr++;
  }
  cout << "Ctr is " << ctr << endl;
  return ctr;
}

void Table::insertValue(IValue *value, int col_index)
{
  m_table[col_index]->addElement(value);
}

void Table::select(int col_index, IValue *value)
{
  int size_col = m_table.getElement(col_index)->getSize();
  int num_col = m_table.getSize();
  for (int i = 0; i < size_col; i++)
  {
    IValue *row_value = m_table.getElement(col_index)->getElement(i);
    if (row_value->is_equal(value))
    {
      for (int j = 0; j < num_col; j++)
      {
        const char *type = new char[7];
        type = m_table.getElement(j)->getType();

        if (strcmp(type, "int") == 0)
        {
          std::cout << m_table.getElement(j)->getElement(i)->getIntValue() << " ";
        }
        if (strcmp(type, "double") == 0)
        {
          std::cout << m_table.getElement(j)->getElement(i)->getDoubleValue() << " ";
        }
        if (strcmp(type, "string") == 0)
        {
          std::cout << m_table.getElement(j)->getElement(i)->getCharValue() << " ";
        }
      }
      std::cout << endl;
    }
  }
}

void Table::updateRows(int search_col_index, IValue *search_value, int target_col_index, IValue *target_value)
{
  int size_search_col = m_table.getElement(search_col_index)->getSize();
  for (int i = 0; i < size_search_col; i++)
  {
    IValue *row_value = m_table.getElement(search_col_index)->getElement(i);
    if (row_value->is_equal(search_value))
    {
      m_table.getElement(target_col_index)->updateElement(i, target_value);
    }
  }
}

void Table::deleteRows(int col_index, IValue *value)
{
  int num_col = m_table.getSize();
  cout << "Num col is" << num_col << endl;
  int size_search_col = m_table.getElement(col_index)->getSize();
  cout << "Num rows is " << size_search_col << endl;
  for (int i = size_search_col - 1; i > -1; i--)
  {
    IValue *row_value = m_table.getElement(col_index)->getElement(i);
    if (row_value->is_equal(value))
    {
      for (int j = 0; j < num_col; j++)
      {
        cout << "Im inside" << endl;
        cout << "For element in column " << j << " and will delete element " << i << endl;
        m_table.getElement(j)->deleteElement(i);
      }
    }
  }
}

void Table::insertRow(int col_index, IValue *value)
{
  m_table[col_index]->addElement(value);
}

void Table::aggregate(int col_index, IValue *value, int target_col_index, const char *operation)
{
  const char *type_search_col = m_table.getElement(col_index)->getType();
  const char *type_target_col = m_table.getElement(target_col_index)->getType();
  const char *type_value = value->getType();
  if ((strcmp(type_search_col, "string") == 0) || (strcmp(type_target_col, "string") == 0) || (strcmp(type_value, "string") == 0))
  {
    cout << "Aggregate columns and value must be of type int or double!" << endl;
    return;
  }

  int size_col = m_table.getElement(col_index)->getSize();
  for (int i = 0; i < size_col; i++)
  {
    IValue *row_value = m_table.getElement(col_index)->getElement(i);
    IValue *target_row_value = m_table.getElement(target_col_index)->getElement(i);
    if (row_value->is_equal(value))
    {

      if (strcmp(operation, "sum") == 0)
      {
        int int_sum = 0;
        double double_sum = 0;
        if (strcmp(type_target_col, "int") == 0)
        {
          int_sum = row_value->getIntValue() + target_row_value->getIntValue();
          IValue *summedInt = new Int(int_sum);
          m_table.getElement(target_col_index)->updateElement(i, summedInt);
        }
        if (strcmp(type_target_col, "double") == 0)
        {
          double_sum = row_value->getDoubleValue() + target_row_value->getDoubleValue();
          IValue *summedDouble = new Double(double_sum);
          m_table.getElement(target_col_index)->updateElement(i, summedDouble);
        }
        continue;
      }

      if (strcmp(operation, "product") == 0)
      {
        int int_product = 0;
        double double_product = 0;
        if (strcmp(type_target_col, "int") == 0)
        {
          int_product = row_value->getIntValue() * target_row_value->getIntValue();
          IValue *productInt = new Int(int_product);
          m_table.getElement(target_col_index)->updateElement(i, productInt);
        }
        if (strcmp(type_target_col, "double") == 0)
        {
          double_product = row_value->getDoubleValue() * target_row_value->getDoubleValue();
          IValue *productDouble = new Double(double_product);
          m_table.getElement(target_col_index)->updateElement(i, productDouble);
        }
        continue;
      }

      if (strcmp(operation, "maximum") == 0)
      {
        if (target_row_value->is_smaller(row_value))
        {
          m_table.getElement(target_col_index)->updateElement(i, row_value);
        }
        continue;
      }

      if (strcmp(operation, "minimum") == 0)
      {
        if (target_row_value->is_bigger(row_value))
        {
          m_table.getElement(target_col_index)->updateElement(i, row_value);
        }
        continue;
      }
    }
  }
}

Table *Table::innerJoin(int first_col_index, Table *other, int other_col_index)
{
  //==creates new table==
  Table *new_table = new Table("Innerjoined");
  const char *first_name_col = m_table[first_col_index]->getNameColumn();
  const char *first_col_type = m_table[first_col_index]->getType();

  const char *second_name_col = other->m_table[other_col_index]->getNameColumn();
  const char *second_col_type = other->m_table[other_col_index]->getType();

  //==adds first column
  new_table->addColumn(first_name_col, first_col_type);
  int size_col = m_table[first_col_index]->getSize();
  for (int i = 0; i < size_col; i++)
  {
    IValue *value = m_table[first_col_index]->getElement(i);
    if (value->isNULL())
    {
      new_table->m_table[0]->addNullElement();
    }
    else
    {
      new_table->m_table[0]->addElement(value);
    }
  }

  //==adds second column
  new_table->addColumn(second_name_col, second_col_type);
  for (int i = 0; i < size_col; i++)
  {
    IValue *value = other->m_table[other_col_index]->getElement(i);
    if (value->isNULL())
    {
      new_table->m_table[1]->addNullElement();
    }
    else
    {
      new_table->m_table[1]->addElement(value);
    }
  }
  return new_table;
}

void Table::rename(const char *new_name)
{
  delete[] m_tablename;
  m_tablename = new char[strlen(new_name) + 1];
  stpcpy(m_tablename, new_name);
}

char *inputValueFromFile(char *input, std::ifstream &infile)
{
  char c;
  unsigned int ctr = 0;
  while (infile.get(c) && (c != '|') && (c != '\0'))
  {
    if ((c != ' ') && (c != '\n') && (c >= '!') && (c <= '~'))
    {
      input[ctr] = c;
      ctr++;
    }
  }
  input[ctr] = '\0';
  return input;
}

char *inputNameFromFile(char *input, std::ifstream &infile)
{
  char c;
  unsigned int ctr = 0;
  while (infile.get(c) && (c != '\n') && (c != '\0'))
  {
    if ((c >= '!') && (c <= '~'))
    {
      input[ctr] = c;
      cout << "At " << ctr << " put " << c << endl;
      ctr++;
    }
  }
  input[ctr] = '\0';
  cout << "Length is" << strlen(input) << endl;
  return input;
}

Table &readTableFromFile(std::ifstream &infile, Table &obj) //FIXME: when adding table to upgrade filename
{
  std::cout << "Im inside importtable function" << endl;
  //==imports filename==
  char *tablename = new char[MAX_TABLENAME_SIZE];
  //infile >> tablename;
  tablename = inputNameFromFile(tablename, infile);
  obj.m_tablename = new char[strlen(tablename) + 1];
  strcpy(obj.m_tablename, tablename);
  cout << "Sucesfully read tablename" << obj.m_tablename << " and size " << strlen(obj.m_tablename) << endl;

  //==imports dimensions of table==
  int num_rows;
  infile >> num_rows;
  int num_col;
  infile >> num_col;
  std::cout << "Dimensions of table are " << num_rows << "X" << num_col << endl;

  //==creates table with empty columns of the given types==
  char *type = new char[7];
  for (int i = 0; i < num_col; i++)
  {
    char *colname = new char[MAX_COLNAME_SIZE];
    infile >> colname;
    infile >> type;
    std::cout << "To add column name of type" << colname << " :" << type << endl;
    obj.addColumn(colname, type);
  }
  std::cout << "Table will have:\n";
  obj.describe();
  infile.get();
  infile.ignore(10000, '\n');
  infile.ignore(10000, '\n');

  //==adds the values for the table==
  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      const char *type = new char[7];
      type = obj.m_table[j]->getType();
      //std::cout << "type is " << type << endl;
      if (strcmp(type, "int") == 0)
      {
        char *initial_input = new char[10000];
        //infile >> initial_input;
        char *input = inputValueFromFile(initial_input, infile);
        cout << "input is ~" << input << endl;
        if (input[0] == 'N')
        {
          cout << "I wont read because its null!Add empty int";
          obj.m_table[j]->addNullElement();
          continue;
        }
        else
        {
          cout << "A value!!" << endl;
          int value;
          value = convertTextToNum(input);
          IValue *int_value = new Int(value);
          obj.m_table[j]->addElement(int_value);

          continue;
        }
      }
      if (strcmp(type, "double") == 0)
      {
        //char *input = new char[100];
        //infile >> input;
        char *initial_input = new char[10000];
        //infile >> initial_input;
        char *input = inputValueFromFile(initial_input, infile);
        cout << "input is ~" << input << endl;
        if (input[0] == 'N')
        {
          cout << "I wont read because its null!Add empty int";
          obj.m_table[j]->addNullElement();
          continue;
        }
        else
        {
          cout << "A value!!" << endl;
          double value = atof(input);
          IValue *double_value = new Double(value);
          obj.m_table[j]->addElement(double_value);
          continue;
        }
      }
      if (strcmp(type, "string") == 0)
      {
        //char *text = new char[MAX_STRING_ROW_SIZE];
        //infile >> text;
        char *initial_input = new char[10000];
        //infile >> initial_input;
        char *input = inputValueFromFile(initial_input, infile);
        cout << "input is ~" << input << endl;
        //std::cout << "[" << i << "][" << j << "] put string text " << text << endl;
        IValue *str_ptr = new String(input);
        cout << "Im about to insert string for column" << j << endl;
        obj.m_table[j]->addElement(str_ptr);
        //FIXME: Maybe insert string should get String&, because othrwise copy constructor
        std::cout << "im here!" << endl;
        continue;
      }
    }
  }
  return obj;
}

void Table::writeTableToFile(std::ofstream &outfile)
{
  std::cout << "Im inside writeTabletoFile function" << endl;

  //==writes tablename==
  outfile << m_tablename << endl;

  //==writes dimensions of table==
  int num_rows = m_table[0]->getSize();
  outfile << num_rows << " ";
  int num_col = m_table.getSize();
  outfile << num_col << endl;
  int table_width = 0;
  const char *type = new char[7];

  //==writes types of every column==
  for (int i = 0; i < num_col; i++)
  {
    outfile << m_table[i]->getNameColumn() << " ";
    outfile << m_table[i]->getType() << endl;
  }

  //====
  outfile << m_table.getElement(0)->getNameColumn() << "|";
  table_width += strlen(m_table.getElement(0)->getNameColumn()) + 1;
  for (int j = 1; j < num_col; j++)
  {
    int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
    int max_row_width = m_table.getElement(j)->getMaxRowWidth();
    if (max_row_width < width_name_column)
    {
      max_row_width = width_name_column;
    }
    table_width += max_row_width + 2;
    outfile << " " << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
  }
  outfile << endl;
  outfile << setfill('-') << setw(table_width) << "|" << endl;

  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      type = m_table.getElement(j)->getType();
      int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
      int max_row_width = m_table.getElement(j)->getMaxRowWidth();
      if (max_row_width < width_name_column)
      {
        max_row_width = width_name_column;
      }

      IValue *row_value = m_table.getElement(j)->getElement(i);
      if (strcmp(type, "int") == 0)
      {
        if (row_value->isNULL())
        {
          outfile << setfill(' ') << setw(max_row_width) << "NULL"
                  << "| ";
          continue;
        }

        outfile << setfill(' ') << setw(max_row_width) << row_value->getIntValue() << "| ";
        continue;
      }
      if (strcmp(type, "double") == 0)
      {
        if (row_value->isNULL())
        {
          outfile << setfill(' ') << setw(max_row_width) << "NULL"
                  << "| ";
          continue;
        }
        outfile << setfill(' ') << setw(max_row_width) << fixed << setprecision(5) << row_value->getDoubleValue() << "| ";
        continue;
      }
      if (strcmp(type, "string") == 0)
      {
        if (row_value->isNULL())
        {
          outfile << setfill(' ') << setw(max_row_width) << "NULL"
                  << "| ";
          continue;
        }
        outfile << setfill(' ') << setw(max_row_width) << row_value->getCharValue() << "| ";
        continue;
      }
    }
    outfile << endl;
  }
}

void Table::print() const
{
  int num_rows = m_table[0]->getSize();
  int num_col = m_table.getSize();
  const char *type = new char[7];
  int table_width = 0;
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  //unsigned short rows_terminal = w.ws_row; //TODO: to implement
  //unsigned short col_terminal = w.ws_col;

  cout << m_table.getElement(0)->getNameColumn() << "|";
  table_width += strlen(m_table.getElement(0)->getNameColumn()) + 1;
  for (int j = 1; j < num_col; j++)
  {
    int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
    int max_row_width = m_table.getElement(j)->getMaxRowWidth();
    if (max_row_width < width_name_column)
    {
      max_row_width = width_name_column;
    }
    table_width += max_row_width + 2;
    cout << " " << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
  }
  cout << endl;
  cout << setfill('-') << setw(table_width) << "|" << endl;

  for (int i = 0; i < num_rows; i++)
  {
    for (int j = 0; j < num_col; j++)
    {
      type = m_table.getElement(j)->getType();
      int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
      int max_row_width = m_table.getElement(j)->getMaxRowWidth();
      if (max_row_width < width_name_column)
      {
        max_row_width = width_name_column;
      }

      IValue *row_value = m_table.getElement(j)->getElement(i);
      if (strcmp(type, "int") == 0)
      {
        if (row_value->isNULL())
        {
          cout << setfill(' ') << setw(max_row_width) << "NULL"
               << "| ";
          continue;
        }

        cout << setfill(' ') << setw(max_row_width) << row_value->getIntValue() << "| ";
        continue;
      }
      if (strcmp(type, "double") == 0)
      {
        if (row_value->isNULL())
        {
          cout << setfill(' ') << setw(max_row_width) << "NULL"
               << "| ";
          continue;
        }
        cout << setfill(' ') << setw(max_row_width) << fixed << setprecision(5) << row_value->getDoubleValue() << "| ";
        continue;
      }
      if (strcmp(type, "string") == 0)
      {
        if (row_value->isNULL())
        {
          cout << setfill(' ') << setw(max_row_width) << "NULL"
               << "| ";
          continue;
        }
        cout << setfill(' ') << setw(max_row_width) << row_value->getCharValue() << "| ";
        continue;
      }
    }
    cout << endl;
  }
}
