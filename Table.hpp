#ifndef _TABLE_HPP_
#define _TABLE_HPP_
#include "List.hpp"
#include "IColumn.hpp"
#include "StringColumn.hpp"
#include "IntColumn.hpp"
#include "DoubleColumn.hpp" 
#include "String.hpp"
#include <fstream>

class Table
{
    List<IColumn*> m_table;
    char* m_tablename; 

    //==helper functions==
    //void createColByType(const char* type, const char* colname);
    //void addRowbyType(const char* type);
    public:
    //--The big 4--
    Table(const char* name="Table");
    Table(const Table&) ;
    Table& operator=(const Table&);
    ~Table();
 
    //--printing and getters
    void describe()const;
    const char* getName() const;
    void print() const; //TODO: dialogue <iomanip>
    void count() const;  //TODO:

    //--table methods 
    bool addColumn(const char* colname, const char* type);
    void insertRow(int col_index);

    void insertIntValue(int value, int col_index);
    void insertDoubleValue(double value, int col_index);
    void insertStringValue(String value, int col_index);
   
    void select(int col_index, int value);
    void select(int col_index, double value);
    void select(int col_index, const char* value); 

    void updateRows(int search_col_index,int search_value,int target_col_index,int target_value);
    void updateRows(int search_col_index,double search_value,int target_col_index,double target_value);
    void updateRows(int search_col_index,String search_value,int target_col_index,const char* target_value);

    void deleteRows(int col_index, int value);
    void deleteRows(int col_index, double value);
    void deleteRows(int col_index, String value);

    void innerJoin();   //TODO:
    void aggregate();   //TODO:
    void rename(const char* new_name);
    friend void writeTableToFile(std::ofstream& outfile, Table& obj); 
    friend Table& readTableFromFile(std::ifstream& infile, Table& obj);
};

 //--files methods
    void writeTableToFile(std::ofstream& outfile, Table& obj); //TODO: 
    Table& readTableFromFile(std::ifstream& infile, Table& obj);  //TODO:



#endif