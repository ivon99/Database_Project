#include <iostream>
#include <fstream>
#include "String.hpp"
#include "IColumn.hpp"
#include "IntColumn.hpp"
#include "DoubleColumn.hpp"
#include "StringColumn.hpp"
#include "List.hpp"
#include "Table.hpp"
using namespace std;

//TODO: Make an interface base class and system to inherit it
//TODO: Make a singleton system

Table &open(const char *filename)
{
    Table *mytable = new Table();
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        //Table mytable;
        readTableFromFile(infile, *mytable);
        cout << "Succesfully read from " << filename << endl;
        infile.close();
        return *mytable;
    }
    else
    { //creates a new empty file
        std::ofstream tmpfile;
        tmpfile.open(filename);
        infile.open(filename);
        cout << "Error in reading " << filename << ". A new filename with this name was generated" << endl;
        if (infile)
        {
            infile.close();
            return *mytable;
        }
        else
        {
            cout << "Error:can't read from file." << endl;
            return *mytable;
        }
    }
}

bool close()
{
    //TODO:deletes all current information of the system, system can't do anything besides command open
    return false;
}
/*
bool save(const char* filename,Table& table)
{
  //TODO: save to the currently opened file
  //database.save(ofstream::file);
  return true;
} */

bool saveas(const char *filepath, Table &table)
{
    std::ofstream outfile;
    outfile.open(filepath);
    if (outfile)
    {
        //TODO:database.save(ofstream::filepath);
        writeTableToFile(outfile, table);
        cout << "Succesfully saved file." << endl;
        outfile.close();
        return true;
    }
    else
    {
        cout << "Error saving file" << endl;
        return false;
    }
}

void help()
{
    cout << "The following commands are supported:\n"
         << "open <file>  \t\t opens <file>\n"
         << "close        \t\t closes currently opened file\n"
         << "save         \t\t saves saves the currently open file\n"
         << "saveas <file>\t\t saves the currently open file in <file>\n"
         << "help         \t\t prints the information" << endl;
}

int main()
{
    /*
    while(true){
    cout<<"Test String by inputting:"<<endl;
    char* test_string= new char[50];
    cin.getline(test_string,50);
    String test(test_string);} */
    /*IntColumn test;
    for(int i=0; i<10; i++)
    {
         test.addRow(i);
    }
    test.printColumn();

    DoubleColumn test2;
    for(int i=10; i<20; i++)
    {
         test.addRow(i);
    }
    test.printColumn(); */
    /* ==Test for describe==
    Table tablename;
    tablename.addColumn("[kitty-katty]","int");
    tablename.addColumn("[babes]","double");
    tablename.describe(); */
    Table test = open("sample_input_update.txt");
    //test.updateRows(0,0,3,5);
    // test.count(0,0);
    test.aggregate(0, 5, 3, "sum");
    test.aggregate(0, 5, 3, "product");
    test.aggregate(0, 5, 3, "maximum");
    test.aggregate(0, 5, 3, "minimum");
    //test.deleteRows(0,0);
    saveas("saved_file.txt", test);

    /* ==Test for String class==
    StringColumn test2;
     char* test_string= new char[50];
    cin.getline(test_string,50);
    String test_stringy(test_string);
    test2.addRow(test_stringy);
    cout<<"Now printing column!!!"<<endl;
    test2.printColumn();
    const char* type= test2.getType();
    cout<<type; */

    return 0;
}
