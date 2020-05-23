#include "System.hpp"
const int MAX_COMMAND_SIZE=20;

System::System()
{
    m_loaded_tables=new List<Table*>();
    m_database= new Database();
    m_index_currently_open_table=0;
}

~System::System()
{
    delete m_database;
}

void System::help()
{
    cout << "The following commands are supported:\n"
         << "open <filename>  \t\t opens a table from <file>\n"
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

Table &open(const char *filename)
{
    Table *mytable = new Table();
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
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

int System::run()
{
    cout<<"Welcome to Project Database. Please enter command:" <<endl;
    char command[MAX_COMMAND_SIZE];
    command[0] = 'z';
    while (strcmp(command, "exit") != 0)
    {
        cin >> command;
        if (strcmp(command, "open") == 0)
        {
            clearCommand(command);
            cin.get();
           // cout << "Im inside open" << endl;
            //Database my_database;
           // List<Table*> loaded_tables;
            char* filename = new char[MAX_FILENAME_SIZE];
            cin >> filename;
            Table *new_table = &open(filename);
            //my_database.addTable(new_table);
            m_loaded_tables.addElement(new_table);
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
                    // save(loaded_tables); //TODO: problem when reading from saved file
                }
                if (strcmp(command, "saveas") == 0)
                {
                    clearCommand(command);
                    cin.get();
                    char* filepath = new char[MAX_FILENAME_SIZE];
                    cin>>filepath;
                    char* tablename = new char[MAX_TABLENAME_SIZE];
                    cin>>tablename;
                    saveasOpen(filepath,tablename,loaded_tables);
                }
                if (strcmp(command, "import") == 0)
                {
                    clearCommand(command);
                    cin.get();
                    int index;
                    cin>>index;
                    my_database.addTable(loaded_tables[index]);
                }
                if(strcmp(command,"showtables")==0)
                {
                    clearCommand(command);
                    cin.get();
                    showtables(loaded_tables);
                }
                if(strcmp(command,"describe")==0)
                {
                    clearCommand(command);
                    cin.get();
                    int index;
                    cin>>index;
                    loaded_tables[index]->describe();
                }
                if(strcmp(command,"print")==0)
                {
                    ;
                }
                if(strcmp(command,"export")==0)  //TODO:to test
                {
                    clearCommand(command);
                    cin.get();
                    int index;
                    cin>>index;
                    char* filename = new char[MAX_FILENAME_SIZE];
                    cin>>filename;
                    saveas(filename,*loaded_tables[index]);
                }
                if(strcmp(command,"")==0)
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

   return 0;
}