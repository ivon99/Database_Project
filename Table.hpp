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

private:
    // prints table from <row_from> and <col_from> till <row_till> and <col_till>
    void printFromTill(int row_from, int row_till, int col_from, int col_till, int table_width) const;
   //prints table without pafination
    void printWithNoPagination() const;
    //returns how many pages due to width should be created
    int findHowManyPagesCols(int num_col, int col_terminal, int pages_indexes[]) const;

public:
    //--The big 4--
    Table(const char *name = "Table");
    Table(const Table &);
    Table &operator=(const Table &);
    ~Table();

    //--printing and getters
    //prints name and type of columns
    void describe() const;
    //returns name of table
    char *getName();
    //returns filename from which table was generated
    char *getFilename() const;
    // prints table on a dialogue window with pagination
    void print() const;
    //sets filename of table
    void setFilename(char *filename);
    void setFilename(const char *filename);
    //adds new column to empty table
    bool addColumn(const char *colname, const char *type);
    //adds new colum to an already existing table
    bool addColumnToExistingTable(const char* colname, const char* type);
    // inserts value at end of column with <col_index>
    void insertRow(int col_index, IValue *value);

    //==methods
    // returns number of rows with given value in column with <col_index>
    int count(int col_index, IValue *value) const;
    //prints all rows which have given value in column with index <column n>
    void select(int col_index, IValue *value);
    //updates all rows in <target column> which have the <search value> in <search column>
    void updateRows(int search_col_index, IValue *search_value, int target_col_index, IValue *target_value);
    // deletes all rows which have <value> in column with <col_index>
    void deleteRows(int col_index, IValue *value);
    // performs operations with values in two different columns
    void aggregate(int col_index, IValue *value, int target_col_index, const char *operation);
    //joins two column of two tables
    Table *innerJoin(int first_col_index, Table *other, int other_col_index); 
    // renames name of table
    void rename(const char *new_name);

    // reads table from file and returns the newly read table
    friend Table &readTableFromFile(std::ifstream &infile, Table &obj);
    // writes table to text file
    void writeTableToFile(std::ofstream &outfile);
};

//--files methods
Table &readTableFromFile(std::ifstream &infile, Table &obj); 
//helper methof, convert text to an int number
int convertTextToNum(char *text);

#endif