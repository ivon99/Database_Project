#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "List.hpp"
#include "Table.hpp"
#include "Database.hpp"

class System
{
  Database *m_database;

  //const char* typeOfInput(char* input);
  bool save_as_for_loaded_tables(char *filepath);
  void showtables() const;
  bool saveas(const char *filepath, Table &table);
  //Table *getOpenedTable(char *filename);
  Table *getOpenedTableByName(char *tablename);

  //===METHODS===
  // void openTable(char *filename);
  void importTable(char *filename);
  void select(int column_n, char *value_input, char *tablename);
  void update(char *tablename, int search_column_n, char *value_input, int target_column_n, char *target_value_input);
  void innerjoin(char *tablename1, int column1, char *tablename_second, int column2);
  void count(char *tablename, int search_column_n, char *search_value_input);
  void aggregate(char *tablename, int search_column_n, char *search_value_input, int target_column_n, char *operation);
  void Delete(char *tablename, int search_column_n, char *search_value_input);
  bool saveDatabase(const char *filename);
  void insert(char *tablename, char *value_input);

public:
  System();
  System(const System &other) = delete;
  System &operator=(const System &other) = delete;
  ~System();
  int run();
  void help();
};

#endif