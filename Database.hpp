#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_
#include "Table.hpp"
#include "List.hpp"
#include "Table.hpp"

class Database
{
    List<Table*> m_database;

    public:
    Table& getTable(const char* tablename) const;
    bool isTable(char* tablename) const;
    bool isTable(const char* tablename) const;
    void showtables()const;
    void addTable(Table* new_table);
    void import(const char* tablename);
    Table& innerJoin(const char* tablename1,int col_index,const char* tablename2,int other_col_index);
    friend void saveDatabaseToFile(std::ofstream& outfile, Database& obj);
    //void save(const char* tablename);
};

 void saveDatabaseToFile(std::ofstream& outfile, Database& obj);

#endif