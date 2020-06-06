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
    int getSizeDatabase() const;
    Table* getTableAtIndex(int index) const;

    Table* getTable(const char* tablename) const;
    bool isTable(char* tablename) const;
    bool isTable(const char* tablename) const;
    void showtables()const;

    void addTable(Table* new_table);
    void import(const char* tablename);
    friend void saveDatabaseToFile(std::ofstream& outfile, Database& obj);
};

 void saveDatabaseToFile(std::ofstream& outfile, Database& obj);

#endif