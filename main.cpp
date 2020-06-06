#include <iostream>
#include <cstring>
#include "System.hpp"
using namespace std;
const int MAX_COMMAND_SIZE = 100;

//TODO: Make an interface base class and system to inherit it
//TODO: Make a singleton system

void help()
{
    cout << "The following commands are supported:\n"
         << "------------------------------------\n"
         << "import <filename>:\n"
         << "adds table from file <filename> to the database\n"
         << "-----\n"
         << "close:\n"
         << "closes currently opened file\n"
         << "-----\n"
         << "save:\n"
         << "saves the currently open file \n"
         << "-----\n"
         << "saveas <filename>:\n"
         << "saves the currently opened tables in <file>\n"
         << "-----\n"
         << "showtables:\n"
         << "prints names of all loaded tables\n"
         << "-----\n"
         << "describe <name>:\n"
         << "prints the type for every column in table <name>\n"
         << "-----\n"
         << "print <name>:\n"
         << "prints table\n"
         << "-----\n"
         << "export <name> <file name>:\n"
         << "saves table in file with <filename>\n"
         << "-----\n"
         << "select <column-n> <value> <tablename>:\n"
         << "prints all rows from given table that contain <value>:\n"
         << "-----\n"
         << "addcolumn <table name> <column name> <column type>:\n"
         << "adds a new column of <column type>\n"
         << "-----\n"
         << "update <table name> <search column n> <search value> <target column n> <target value>:\n"
         << "updates all rows in <target column> which have the <search value> in <search column>\n"
         << "-----\n"
         << "insert <table name> <column1> ... <column n>:\n"
         << "adds new row and inserts <value> at <serach column>\n"
         << "-----\n"
         << "delete <table name> <searc column> <search value>:\n"
         << "deletes value in <search column>\n"
         << "-----\n"
         << "innerjoin <table1> <column1> <table2> <column 2>:\n"
         << "innerjoins columns and produces a new table\n"
         << "-----\n"
         << "rename <old name> <new name>:\n"
         << "renames table\n"
         << "-----\n"
         << "count <table name> <search column> <search value>:\n"
         << "counts all rows whose column has <search value>\n"
         << "-----\n"
         << "aggregate <table name> <search column> <search value> <target column> <operaton>:\n"
         << "performs <operation> in <target column> on all rows which columns have <search calue>\n"
         << "-----\n"
         << "help:\n"
         << "prints methods information\n"
         << "--------------------------" << endl;
}

int main()
{
    cout << "Welcome to Project Database. Please enter command:" << endl;
    char *command = new char[MAX_COMMAND_SIZE];
    command[0]='z';
    while (strcmp(command, "exit") != 0)
    {
        cin>>command;
        if (strcmp(command, "import") == 0)
        {
            System new_system;
            if(new_system.run()==0)
            {
                return 0;
            }
            continue;
        }
        if(strcmp(command,"help")==0)
        {
           help();
           continue;
        }
        else if(strcmp(command,"exit")!=0)
        {
            cout << "Command not recognised! Try importing a table from file or try help." << endl;
            continue;
        }
    }
    cout<<"Thank you for using Database! See you again."<<endl;

    return 0;
}