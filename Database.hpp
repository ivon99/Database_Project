#ifndef _DATABASE_HPP_
#define _DATABASE_HPP_
#include "Table.hpp"
#include "List.hpp"

class Database
{
    List<Table*> m_database;

    public:
    bool isTable(const char* tablename) const;
    void showtables()const;
    void addTable(const char* tablename);
    //void save(const char* tablename);
};

#endif