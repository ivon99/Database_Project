#include <iostream>
#include <fstream>
#include "String.hpp"
#include "IColumn.hpp"
#include "IntColumn.hpp"
#include "DoubleColumn.hpp"
#include "StringColumn.hpp"
#include "List.hpp"
#include "Table.hpp"
#include "Database.hpp"
#include <cstring>
using namespace std;
const int MAX_COMMAND_SIZE = 100;
const int MAX_FILENAME_SIZE = 100;

//TODO: Make an interface base class and system to inherit it
//TODO: Make a singleton system

void clearCommand(char command[])
{
    for (int i = 0; i < 20; i++)
    {
        command[i] = ' ';
    }
}

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

bool save(List<Table*>& loaded_tables)
{
    int size_loaded_tables = loaded_tables.getSize();
    for (int i = 0; i < size_loaded_tables; i++)
    {
        const char *filename = loaded_tables[i]->getFilename();
        std::ofstream outfile;
        outfile.open(filename);
        if (outfile)
        {
            writeTableToFile(outfile, *loaded_tables[i]);
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
    return true;
}

bool saveas(const char *filepath, Table &table)
{
    std::ofstream outfile;
    outfile.open(filepath);
    if (outfile)
    {
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
         << "open <filename>  \t\t opens <file>\n"
         << "close            \t\t closes currently opened file\n"
         << "save             \t\t saves the currently open file\n"
         << "saveas <filename>\t\t saves the currently open file in <file>\n"
         << "import <filename>\t\t adds table from file <filename> to the database\n"
         << "showtables       \t\t prints names of all loaded tables\n"
         << "describe <name>  \t\t prints the type for every column in table <name>\n"
         << "print <name>     \t\t prints table \n"
         << "export <name> <file name>                         \t\t saves table in file with <filename>\n"
         << "select <column-n> <value> <tablename>             \t\t prints all rows from given table that contain <value>\n"
         << "addcolumn <table name> <column name> <column type>\t\t adds a new column of <column type>\n"
         << "update <table name> <search column n> <search value> <target column n> <target value>\n updates all rows in <target column> which have the <search value> in <search column>\n"
         << "insert <table name> <column1> ... <column n>      \t\t adds new row and inserts <value> at <serach column>\n"
         << "delete <table name> <searc column> <search value> \t\t deletes value in <search column>\n"
         << "innerjoin <table1> <column1> <table2> <column 2>  \t\t interjoins columns and produces a new table\n"
         << "rename <old name> <new name>                      \t\t renames table"
         << "count <table name> <search column> <search value> \t\t counts all rows whose column has <search value>\n"
         << "aggregate <table name> <search column> <search value> <target column> <operaton>\n performs <operation> in <target column> on all rows which columns have <search calue>"
         << "help         \t\t prints methods information" << endl;
}

int main()
{
    cout << "Welcome to Project Database. Please enter command:" << endl;
    char command[MAX_COMMAND_SIZE];
    command[0] = 'z';
    while (strcmp(command, "exit") != 0)
    {
        cin >> command;
        if (strcmp(command, "open") == 0)
        {
            clearCommand(command);
            cin.get();
            cout << "Im inside open" << endl;

            Database my_database;
            List<Table*> loaded_tables;
            char filename[MAX_FILENAME_SIZE];
            cin >> filename;
            Table *new_table = &open(filename);
            my_database.addTable(new_table);
            loaded_tables.addElement(new_table);
            command[0]='z';
            while ((strcmp(command, "close") != 0))
            {
                cin>>command;
                if (strcmp(command, "open") == 0)
                {
                    clearCommand(command);
                    cin.get();
                    char filename[MAX_FILENAME_SIZE];
                    cin >> filename;
                    Table *new_table = &open(filename);
                    loaded_tables.addElement(new_table);
                    cout<<"Added table to loaded tables and now it has size" << loaded_tables.getSize()<<endl;
                    //writeTableToFile()
                    //my_database.addTable(new_table);
                }
                if (strcmp(command, "save") == 0)
                {
                    clearCommand(command);
                    cin.get();
                    save(loaded_tables);
                }
                if (strcmp(command, "") == 0)
                {
                    ;
                }
                if (strcmp(command, "") == 0)
                {
                    ;
                }
                if (strcmp(command,"exit") == 0)
                {
                    cout<<"Im inside exit"<<endl;
                    return 0;
                }
            }
        }
        if (strcmp(command, "help") == 0)
        {
            help();
        }
    }
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
    /* Table test1 = open("table1.txt");
    Table test2 = open("simple.txt");    */
    //test1.describe();
    //test2.describe();
    //Table innerjoined= test1.innerJoin(3,test2,0); //TODO: in
    //saveas("interjoined.txt", innerjoined);
    //test1.updateRows(0,0,3,5);
    // test1.count(0,0);
    //test1.aggregate(0, 5, 3, "sum");
    //test1.aggregate(0, 5, 3, "product");
    //test1.aggregate(0, 5, 3, "maximum");
    //test1.aggregate(0, 5, 2, "minimum");
    //test1.deleteRows(0,0);
    // saveas("saved_file.txt", test1);
    //saveas("save2file.txt",test2);
    /*  
    Database my_database;
    Table* test1_ptr = &test1;
    my_database.addTable(test1_ptr);
    Table* test2_ptr = &test2;
    my_database.addTable(test2_ptr);
    my_database.showtables();  */

    /*
    char input[10];
    cin>>input;
    input[strlen(input)+1]='\0';
    cout<<strlen(input); 
    */

    //bool is_2= my_database.isTable(input);
    //cout<<is_2<<endl;
    //bool is_1 = my_database.isTable("Table1");
    //cout<<is_1<<endl;
    //Table innerjoined=  my_database.innerJoin("Table1",0,"Table2",0);
    //saveas("innerjoined.txt", innerjoined);

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
    /*
    Table test1;
    test1.addColumn("mystingcol","string");
    test1.describe();
    char* text = new char[100];
        cin>> text;
        //String *str_ptr = new String(text);
        String newString(text);
        std::cout << "string now is" <<newString<<endl;
        // const char* value_in= str_ptr->convertToChar();
        //cout<<value_in;
        cout<<"Im about to insert string"<<endl;
        test1.insertStringValue(newString, 0);  //FIXME: Maybe insert string should get String&, because othrwise copy constructor
        std::cout << "im here!" << endl;
        char* text1 = new char[100];
        cin>> text1;
        //String *str_ptr = new String(text);
        String newString2(text1);
        std::cout << "string now is" <<newString<<endl;
        // const char* value_in= str_ptr->convertToChar();
        //cout<<value_in;
        cout<<"Im about to insert string"<<endl;
        test1.insertStringValue(newString2, 0);  
        std::cout << "im here!" << endl; */

    return 0;
}
