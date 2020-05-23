#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_
#include "List.hpp"
#include "Table.hpp"
#include "Database.hpp"

class System
{
  List<Table*> m_loaded_tables;
  int m_index_currently_open_table;
  Database* m_database;

  public::
  System();
  System(const System& other) =delete;
  System& operator=(const System& other) =delete;
  ~System();
  int run();
  void help();


};

#endif