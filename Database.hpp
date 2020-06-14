#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_
#include "Table.hpp"
#include "List.hpp"
#include "Table.hpp"

class Database
{
    List<Table*> m_database;

    public:
    //===getters 
    // returns num of loaded tables in database
    int getSizeDatabase() const;
    // returns pointer to table at <index?
    Table* getTableAtIndex(int index) const;

    //returns pointer to table with <tablename>
    Table* getTable(const char* tablename) const;
    // returns true if found loaded table with <tablename>
    bool isTable(char* tablename) const;
    // returns true if found loaded table with <tablename>
    bool isTable(const char* tablename) const;

    // adds table <new_table> to database
    void addTable(Table* new_table);
    // import table with <tablename> to database
    void import(const char* tablename);
    // writes database to file
    friend void saveDatabaseToFile(std::ofstream& outfile, Database& obj);
};

 void saveDatabaseToFile(std::ofstream& outfile, Database& obj);

#endif