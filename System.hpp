#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "List.hpp"
#include "Table.hpp"
#include "Database.hpp"

class System
{
  Database *m_database;

private:
  //saves all loaded tables in one file 
  bool save_as_for_loaded_tables(char *filepath);
  //shows loaded tables in database
  void showtables() const;
  //saves table to file with <filename>
  bool saveas(const char *filename, Table &table);
  //returns pointer to table with <tablename>
  Table *getOpenedTableByName(char *tablename);
  //loads a table from <filename>
  //returns newle read table 
  Table &open(const char *filename);

  //===METHODS===
  //imports a table from a file
  void importTable(char *filename);
  //prints all rows which have given value in column with index <column n>
  void select(int column_n, char *value_input, char *tablename);
  //updates all rows in <target column> which have the <search value> in <search column>
  void update(char *tablename, int search_column_n, char *value_input, int target_column_n, char *target_value_input);
  //innerjoines two columns from two given tables
  void innerjoin(char *tablename1, int column1, char *tablename_second, int column2);
  //prints how many rows in given column have the given value
  void count(char *tablename, int search_column_n, char *search_value_input);
  //performs operation on values of <search_column_n> onto <search_value_n>
  void aggregate(char *tablename, int search_column_n, char *search_value_input, int target_column_n, char *operation);
  //delete rows which have <search_value> in <search_column>
  void Delete(char *tablename, int search_column_n, char *search_value_input);
  //saves current database to file with <filename>
  bool saveDatabase(const char *filename);
  // inserts new row of values in table with <tablename>
  void insert(char *tablename, char *value_input);

public:
  System();
  System(const System &other) = delete;
  System &operator=(const System &other) = delete;
  ~System();
  int run();
  //prints supported functionalities
  void help();
};

#endif