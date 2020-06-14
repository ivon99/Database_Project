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
const unsigned int MAX_INPUT_SIZE = 10000;

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
  m_tablename = new char[strlen(other.m_tablename) + 1];
  strcpy(m_tablename, other.m_tablename);
  m_filename = new char[strlen(other.m_filename) + 1];
  strcpy(m_filename, other.m_filename);
  m_table = other.m_table;
}

Table &Table::operator=(const Table &other)
{
  if (this != &other)
  {
    delete[] m_tablename;
    delete[] m_filename;
    m_tablename = new char[strlen(other.m_tablename) + 1];
    strcpy(m_tablename, other.m_tablename);
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
    return true;
  }
  if (strcmp(type, "int") == 0)
  {
    IColumn *col = new IntColumn(colname);
    m_table.addElement(col);
    return true;
  }
  if (strcmp(type, "double") == 0)
  {
    IColumn *col = new DoubleColumn(colname);
    m_table.addElement(col);
    return true;
  }
  else
  {
    std::cout << "Invalid type for new column." << std::endl;
    return false;
  }
}

bool Table::addColumnToExistingTable(const char *colname, const char *type)
{
  int rows = m_table[0]->getSize();
  if (strcmp(type, "string") == 0)
  {
    IColumn *col = new StringColumn(colname, rows);
    m_table.addElement(col);
    return true;
  }
  if (strcmp(type, "int") == 0)
  {
    IColumn *col = new IntColumn(colname, rows);
    m_table.addElement(col);
    return true;
  }
  if (strcmp(type, "double") == 0)
  {
    IColumn *col = new DoubleColumn(colname, rows);
    m_table.addElement(col);
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
  cout << "Number or rows is : " << ctr << endl;
  return ctr;
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
  int size_search_col = m_table.getElement(col_index)->getSize();
  for (int i = size_search_col - 1; i > -1; i--)
  {
    IValue *row_value = m_table.getElement(col_index)->getElement(i);
    if (row_value->is_equal(value))
    {
      for (int j = 0; j < num_col; j++)
      {
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

//== read from file helper functions
/*inputs only characters, ignores column pipe, spaces and newlines*/
char *inputValueFromFile(char *input, std::ifstream &infile)
{
  char c;
  unsigned int ctr = 0;
  bool inside_string = false;
  while (infile.get(c) && (c != '|') && (c != '\0'))
  {
    if (c == '\"')
      inside_string = true;
    if ((c == ' ') && (inside_string))
    {
      input[ctr] = c;
      ctr++;
      continue;
    }
    if ((c != '\n') && (c >= '!') && (c <= '~') && (c != ' '))
    {
      input[ctr] = c;
      ctr++;
    }
  }
  input[ctr] = '\0';
  return input;
}

/*inputs tablename from file*/
char *inputNameFromFile(char *input, std::ifstream &infile)
{
  char c;
  unsigned int ctr = 0;
  while (infile.get(c) && (c != '\n') && (c != '\0'))
  {
    if ((c >= '!') && (c <= '~'))
    {
      input[ctr] = c;
      ctr++;
    }
  }
  input[ctr] = '\0';
  return input;
}

Table &readTableFromFile(std::ifstream &infile, Table &obj)
{
  //==imports filename==
  char *tablename = new char[MAX_TABLENAME_SIZE];
  tablename = inputNameFromFile(tablename, infile);
  obj.m_tablename = new char[strlen(tablename) + 1];
  strcpy(obj.m_tablename, tablename);

  //==imports dimensions of table==
  int num_rows;
  infile >> num_rows;
  int num_col;
  infile >> num_col;

  //==creates table with empty columns of the given types==
  char *type = new char[7];
  for (int i = 0; i < num_col; i++)
  {
    char *colname = new char[MAX_COLNAME_SIZE];
    infile >> colname;
    infile >> type;
    obj.addColumn(colname, type);
  }
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
      if (strcmp(type, "int") == 0)
      {
        char *initial_input = new char[MAX_INPUT_SIZE];
        char *input = inputValueFromFile(initial_input, infile);
        if (input[0] == 'N') //if NULL, add null int
        {
          obj.m_table[j]->addNullElement();
          continue;
        }
        else
        {
          int value;
          value = convertTextToNum(input);
          IValue *int_value = new Int(value);
          obj.m_table[j]->addElement(int_value);
          continue;
        }
      }
      if (strcmp(type, "double") == 0)
      {
        char *initial_input = new char[MAX_INPUT_SIZE];
        char *input = inputValueFromFile(initial_input, infile);
        if (input[0] == 'N') //if null, add null double
        {
          obj.m_table[j]->addNullElement();
          continue;
        }
        else
        {
          double value = atof(input); //convert char array input to double
          IValue *double_value = new Double(value);
          obj.m_table[j]->addElement(double_value);
          continue;
        }
      }
      if (strcmp(type, "string") == 0)
      {
        char *initial_input = new char[MAX_INPUT_SIZE];
        char *input = inputValueFromFile(initial_input, infile);
        IValue *str_ptr = new String(input);
        obj.m_table[j]->addElement(str_ptr);
        continue;
      }
    }
  }
  return obj;
}

void Table::writeTableToFile(std::ofstream &outfile)
{
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
  for (int j = 0; j < num_col; j++)
  {
    int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
    int max_row_width = m_table.getElement(j)->getMaxRowWidth();
    if (max_row_width < width_name_column)
    {
      max_row_width = width_name_column;
    }
    table_width += max_row_width + 2;
    if (j == 0)
    {
      outfile << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
      continue;
    }
    outfile << " " << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
  }
  outfile << endl;
  outfile << setfill('-') << setw(table_width - 1) << "|" << endl;

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

void Table::printWithNoPagination() const
{
  int num_rows = m_table[0]->getSize();
  int num_col = m_table.getSize();
  const char *type = new char[7];
  int table_width = 0;

  for (int j = 0; j < num_col; j++)
  {
    int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
    int max_row_width = m_table.getElement(j)->getMaxRowWidth();
    if (max_row_width < width_name_column)
    {
      max_row_width = width_name_column;
    }
    table_width += max_row_width + 2;
    if (j == 0)
    {
      cout << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
      continue;
    }
    cout << " " << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
  }
  cout << endl;
  cout << setfill('-') << setw(table_width - 1) << "|" << endl;

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

void Table::printFromTill(int row_from, int row_till, int col_from, int col_till, int table_width) const
{
  const char *type = new char[7];
  bool one_on_page = false;
  if (col_from == (col_till - 1))
    one_on_page = true;
  if (row_from == 0)
  {
    for (int j = col_from; j < col_till; j++)
    {
      if ((j == 0) || (one_on_page))
      {
        int width_name_column = strlen(m_table.getElement(j)->getNameColumn());
        int max_row_width = m_table.getElement(j)->getMaxRowWidth();
        if (max_row_width < width_name_column)
        {
          max_row_width = width_name_column;
        }
        table_width += max_row_width + 1;
        cout << setw(max_row_width) << m_table.getElement(j)->getNameColumn() << "|";
      }
      else
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
    }
    cout << endl;
  }
  for (int i = row_from; i < row_till; i++)
  {
    for (int j = col_from; j < col_till; j++)
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

int Table::findHowManyPagesCols(int num_col, int col_terminal, int pages_indexes[]) const
{
  int index_pages = 1;
  int sum = 2;
  for (int i = 0; i < num_col; i++)
  {

    //calculating pages for width paginations
    int width_name_column = strlen(m_table.getElement(i)->getNameColumn());
    int max_at_index = m_table.getElement(i)->getMaxRowWidth() + 1;
    if (max_at_index < width_name_column)
    {
      max_at_index = width_name_column + 1;
    }
    sum += max_at_index;
    if (sum >= col_terminal)
    {
      pages_indexes[index_pages] = i - 1;
      index_pages++;
      sum = max_at_index;
      if (sum >= col_terminal)
      {
        pages_indexes[index_pages] = i;
        index_pages++;
        continue;
      }
      continue;
    }
    if (i == (num_col - 1))
    {
      pages_indexes[index_pages] = i;
      index_pages++;
    }
  }

  pages_indexes[index_pages] = num_col - 1;
  index_pages++;

  return index_pages;
}

void Table::print() const
{
  int num_rows = m_table[0]->getSize();
  int num_col = m_table.getSize();

  unsigned int table_width = 0;

  //===findinf the dimensions of dialogue window===
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  unsigned short rows_terminal = w.ws_row;
  unsigned short col_terminal = w.ws_col;

  char *pagination_command = new char[10];
  pagination_command[0] = 'z';

  //==calculating total table width===
  for (int i = 0; i < num_col; i++)
  {
    int width_name_column = strlen(m_table.getElement(i)->getNameColumn());
    int max_row_width = m_table.getElement(i)->getMaxRowWidth();
    if (max_row_width < width_name_column)
    {
      max_row_width = width_name_column;
    }
    table_width += max_row_width + 1;
  }

  //===if table doesnt fit in window===
  if ((col_terminal <= table_width) || (rows_terminal <= num_rows))
  {
    int index_pages = 1;
    //holds the indexes of columns for width pagination
    int pages_indexes[num_col] = {
        -1,
    };
    if (table_width > col_terminal)
      index_pages = findHowManyPagesCols(num_col, col_terminal, pages_indexes);
    else
    {
      pages_indexes[1] = num_col - 1; //if no need for horizontal pagination
      index_pages = 2;                //thre is only one page (two indexes: begining and end)
    }

    int printed_rows = 0; //holds how many rows of table have been printed so far
    int rows_left_to_print = 0;
    int rows_initial = 0;           //holds index of row from which to start printing next page
    int last_page_printed_rows = 0; // holds how many printed rows last printed page had
    int previous_page_index = 0;    // holds column index of the previous page
    bool printed_all_width = false;

    if (num_rows > rows_terminal) //if rows dont fit in window
    {
      printFromTill(0, rows_terminal, 0, pages_indexes[1] + 1, table_width); //print all row till end of window and forst page
      if (pages_indexes[1] == (num_col - 1))
      {
        printed_all_width = true;
        previous_page_index = 0;
      }
      else
      {
        previous_page_index++;
      }
      printed_rows = rows_terminal;
      rows_initial = rows_terminal;
      last_page_printed_rows = rows_terminal;
    }
    else if (num_rows < rows_terminal) //if rows fit in window
    {
      printFromTill(0, num_rows, 0, pages_indexes[1] + 1, table_width); // print all rows
      if (pages_indexes[1] == (num_col - 1))
      {
        printed_all_width = true;
        previous_page_index = 0;
      }
      else
      {
        previous_page_index++;
      }
      printed_rows = num_rows;
      rows_initial = num_rows;
      last_page_printed_rows = num_rows;
    }
    rows_left_to_print = num_rows - printed_rows;
    //==implementing commands for pages==

    while (strcmp(pagination_command, "exit") != 0)
    {
      cin >> pagination_command;
      if (strcmp(pagination_command, "next") == 0)
      {
        //when we couldnt fit a whole page and there is more rows to print
        if (rows_left_to_print >= rows_terminal)
        {
          if ((printed_all_width) && (rows_left_to_print > 0))
          {
            printFromTill(rows_initial, rows_initial + rows_terminal, pages_indexes[previous_page_index] + 1, pages_indexes[previous_page_index + 1] + 1, table_width);
            last_page_printed_rows = rows_terminal;
            printed_rows += rows_terminal;
            rows_initial = rows_initial + rows_terminal;
          }
          else if (!printed_all_width)
          {
            int new_index = rows_initial - last_page_printed_rows;
            printFromTill(new_index, new_index + (last_page_printed_rows ), pages_indexes[previous_page_index] + 1, pages_indexes[previous_page_index + 1] + 1, table_width);
            last_page_printed_rows = last_page_printed_rows;
            printed_rows = new_index + (last_page_printed_rows);
            rows_initial = new_index + (last_page_printed_rows);
          }

          if (pages_indexes[previous_page_index + 1] == (num_col - 1))
          {
            previous_page_index = 0;
            printed_all_width = true;
          }
          else
          {
            printed_all_width = false;
            previous_page_index++;
          }
          rows_left_to_print = num_rows - printed_rows;
        }
        //when we could print all the other rows
        else if (rows_left_to_print < rows_terminal)
        {
          if ((printed_all_width) && (rows_left_to_print > 0))
          {
            printFromTill(rows_initial, rows_initial + rows_left_to_print, pages_indexes[previous_page_index] + 1, pages_indexes[previous_page_index + 1] + 1, table_width);
            last_page_printed_rows = rows_left_to_print;
            printed_rows += rows_left_to_print;
            rows_initial = rows_initial + rows_left_to_print;
            if (pages_indexes[previous_page_index] == (num_col - 1))
            {
              previous_page_index = 0;
              printed_all_width = true;
            }
            else
            {
              previous_page_index++;
              printed_all_width = false;
            }
          }
          else if (!printed_all_width)
          {
            int new_index = rows_initial - last_page_printed_rows;
            printFromTill(new_index, new_index + (last_page_printed_rows ), pages_indexes[previous_page_index] + 1, pages_indexes[previous_page_index + 1] + 1, table_width);
            last_page_printed_rows  = last_page_printed_rows;
            printed_rows = new_index + (last_page_printed_rows);
            rows_initial = new_index + (last_page_printed_rows);
            if (pages_indexes[previous_page_index + 1] == (num_col - 1))
            {
              previous_page_index = 0;
              printed_all_width = true;
            }
            else
            {
              previous_page_index++;
              printed_all_width = false;
            }
          }
          rows_left_to_print = num_rows - printed_rows;
        }
      }
      if (strcmp(pagination_command, "previous") == 0)
      {
        if(pages_indexes[previous_page_index]==-1)
        {
          printFromTill( printed_rows-last_page_printed_rows,last_page_printed_rows, 0, pages_indexes[1] + 1, table_width);
        }
        else
        printFromTill( printed_rows-last_page_printed_rows,last_page_printed_rows, pages_indexes[previous_page_index-1] + 1, pages_indexes[previous_page_index] + 1, table_width);
        rows_initial = last_page_printed_rows;
        printed_rows = last_page_printed_rows;
        last_page_printed_rows = last_page_printed_rows - (printed_rows - last_page_printed_rows);
        printed_rows = printed_rows - last_page_printed_rows;
      }
    }
  }
  else
  { //if table fits in window, print without paginating it
    printWithNoPagination();
  }
}
