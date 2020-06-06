#ifndef _TABLE_HPP_
#define _TABLE_HPP_
#include "List.hpp"
#include "IColumn.hpp"
#include "StringColumn.hpp"
#include "IntColumn.hpp"
#include "DoubleColumn.hpp"
#include "String.hpp"
#include "IValue.hpp"
#include <fstream>

class Table
{
    List<IColumn *> m_table;
    char *m_tablename;
    char *m_filename;

public:
    //--The big 4--
    Table(const char *name = "Table");
    Table(const Table &);
    Table &operator=(const Table &);
    ~Table();

    //--printing and getters
    void describe() const;
    char *getName();
    char *getFilename() const;
    void print() const; //TODO: dialogue <iomanip>
    void setFilename(char *filename);
    bool addColumn(const char *colname, const char *type);
    void insertRow(int col_index, IValue *value);

    //==setters==
    void setFilename(const char *filename);

    //==methods
    int count(int col_index, IValue *value) const;
    void insertValue(IValue *value, int col_index);
    void select(int col_index, IValue *value);
    void updateRows(int search_col_index, IValue *search_value, int target_col_index, IValue *target_value);
    void deleteRows(int col_index, IValue *value);
    void aggregate(int col_index, IValue *value, int target_col_index, const char *operation);

    Table *innerJoin(int first_col_index, Table *other, int other_col_index); //TODO:
    void rename(const char *new_name);

    friend Table &readTableFromFile(std::ifstream &infile, Table &obj);
    void writeTableToFile(std::ofstream &outfile);
};

//--files methods
Table &readTableFromFile(std::ifstream &infile, Table &obj); //TODO:
int convertTextToNum(char *text);

#endif