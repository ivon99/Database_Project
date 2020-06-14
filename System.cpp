#include "System.hpp"
#include <cstring>
#include <cmath>
const int MAX_COMMAND_SIZE = 20;
const int MAX_FILENAME_SIZE = 50;
const int MAX_COLUMN_NAME = 100;
const int MAX_TABLENAME_SIZE = 1000;
const int MAX_ROW_VALUE_LENGTH = 1000;
const int MAX_TYPENAME_LENGTH = 7;
const int MAX_OPERATION_SIZE = 8;

//===helper functions===
/*returns type of input */
const char *typeOfInput(char *value)
{
    int size = strlen(value);
    bool double_dot = false;
    for (int i = 0; i < size; i++)
    {
        if ((value[i] < '0') || (value[i] > '9')) //checks if not a char
        {
            if ((value[i] != '+') && (value[i] != '-') && (value[i] != '.'))
            {
                return "string";
            }
            if ((value[i] == '.'))
            {
                double_dot = true;
            }
        }
    }
    if (double_dot)
        return "double";
    else
        return "int";
}

/*converts an array of char to int*/
int charToNum(char *input)
{
    int number = 0;
    int digit;
    int size = strlen(input);
    int exponent = -1;
    for (int i = size - 1; i >= 0; i--)
    {
        digit = input[i] - '0';
        exponent++;
        number += digit * pow(10, exponent);
    }
    return number;
}

//===THE BIG 4===
System::System()
{
    m_database = new Database();
}

System::~System()
{
    delete m_database;
}

//=== helper functions

Table *System::getOpenedTableByName(char *tablename)
{
    int size_loaded_tables = m_database->getSizeDatabase();
    for (int i = 0; i < size_loaded_tables; i++)
    {
        char *tablename_at_index = m_database->getTableAtIndex(i)->getName();
        if (strcmp(tablename_at_index, tablename) == 0)
        {
            return m_database->getTableAtIndex(i);
        }
    }
    cout << "Unable to find a table by that name!" << endl;
    return nullptr;
}

bool System::saveas(const char *filename, Table &table)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        table.writeTableToFile(outfile);
        cout << "Succesfully saved file " << filename << endl;
        outfile.close();
        return true;
    }
    else
    {
        cout << "Error saving file" << endl;
        return false;
    }
}

bool System::saveDatabase(const char *filename)
{
    std::ofstream outfile;
    outfile.open(filename);
    if (outfile)
    {
        saveDatabaseToFile(outfile, *m_database);
        cout << "Saved database to file " << filename << endl;
        outfile.close();
        return true;
    }
    else
    {
        cout << "Error saving file" << endl;
        return false;
    }
}

bool System::save_as_for_loaded_tables(char *filepath)
{
    std::ofstream outfile;
    outfile.open(filepath, std::ofstream::out | std::ofstream::app);
    if (outfile)
    {
        int size_loaded_tables = m_database->getSizeDatabase();
        for (int i = 0; i < size_loaded_tables; i++)
        {
            m_database->getTableAtIndex(i)->writeTableToFile(outfile);
            cout << "Succesfully saved to file " << filepath << endl;
        }
        outfile.close();
        return true;
    }
    else
    {
        cout << "Error saving file" << endl;
        return false;
    }
}

void System::showtables() const
{
    int size = m_database->getSizeDatabase();
    for (int i = 0; i < size; i++)
    {
        cout << "Table #" << i << ":" << m_database->getTableAtIndex(i)->getName()
             << " imported from " << m_database->getTableAtIndex(i)->getFilename() << endl;
    }
}

void System::help()
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
         << "saves the currently opened tables in their respective files\n"
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

Table &System::open(const char *filename)
{
    Table *mytable = new Table();
    std::ifstream infile;
    infile.open(filename);
    if (infile)
    {
        Table *read_table = &readTableFromFile(infile, *mytable);
        read_table->setFilename(filename);
        cout << "Succesfully read from " << read_table->getFilename() << endl;
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

//===SYSTEM METHODS==

void System::importTable(char *filename)
{
    Table *new_table = &open(filename);
    m_database->addTable(new_table);
}

void System::select(int column_n, char *value_input, char *tablename)
{
    const char *type_value = typeOfInput(value_input);
    IValue *value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(value_input);
        value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(value_input);
        value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        value = new String(value_input);
    }
    Table *table_to_select = getOpenedTableByName(tablename);
    table_to_select->select(column_n, value);
}

void System::update(char *tablename, int search_column_n, char *value_input, int target_column_n, char *target_value_input)
{
    const char *type_value = typeOfInput(value_input);
    IValue *value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(value_input);
        value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(value_input);
        value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        value = new String(value_input);
    }

    type_value = typeOfInput(target_value_input);
    IValue *target_value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(target_value_input);
        target_value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(target_value_input);
        target_value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        target_value = new String(target_value_input);
    }
    Table *table_to_update = getOpenedTableByName(tablename);
    table_to_update->updateRows(search_column_n, value, target_column_n, target_value);
}

void System::innerjoin(char *tablename1, int column1, char *tablename_second, int column2)
{
    Table *table1 = getOpenedTableByName(tablename1);
    Table *table_second = getOpenedTableByName(tablename_second);
    Table *innerjoined_table = table1->innerJoin(column1, table_second, column2);
    cout << "Innerjoined tablename is" << innerjoined_table->getName();
    m_database->addTable(innerjoined_table);
}

void System::count(char *tablename, int search_column_n, char *search_value_input)
{
    const char *type_value = typeOfInput(search_value_input);
    IValue *search_value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(search_value_input);
        search_value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(search_value_input);
        search_value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        search_value = new String(search_value_input);
    }
    Table *table_to_count = getOpenedTableByName(tablename);
    table_to_count->count(search_column_n, search_value);
}

void System::aggregate(char *tablename, int search_column_n, char *search_value_input, int target_column_n, char *operation)
{
    const char *type_value = typeOfInput(search_value_input);
    IValue *search_value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(search_value_input);
        search_value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(search_value_input);
        search_value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        search_value = new String(search_value_input);
    }
    Table *table_to_aggregate = getOpenedTableByName(tablename);
    table_to_aggregate->aggregate(search_column_n, search_value, target_column_n, operation);
}

void System::Delete(char *tablename, int search_column_n, char *search_value_input)
{
    const char *type_value = typeOfInput(search_value_input);
    IValue *target_value = nullptr;
    if (strcmp(type_value, "int") == 0)
    {
        int num = charToNum(search_value_input);
        target_value = new Int(num);
    }
    if (strcmp(type_value, "double") == 0)
    {
        double double_num = atof(search_value_input);
        target_value = new Double(double_num);
    }
    if (strcmp(type_value, "string") == 0)
    {
        target_value = new String(search_value_input);
    }
    Table *table_to_delete_in = getOpenedTableByName(tablename);
    table_to_delete_in->deleteRows(search_column_n, target_value);
}

void System::insert(char *tablename, char *value_input)
{
    int col_index = 0;
    while (cin.peek() != '\n')
    {
        cin >> value_input;
        const char *type_value = typeOfInput(value_input);
        IValue *value = nullptr;
        if (strcmp(type_value, "int") == 0)
        {
            int num = charToNum(value_input);
            value = new Int(num);
            getOpenedTableByName(tablename)->insertRow(col_index, value);
            col_index++;
            continue;
        }
        if (strcmp(type_value, "double") == 0)
        {
            double double_num = atof(value_input);
            value = new Double(double_num);
            getOpenedTableByName(tablename)->insertRow(col_index, value);
            col_index++;
            continue;
        }
        if (strcmp(type_value, "string") == 0)
        {
            value = new String(value_input);
            getOpenedTableByName(tablename)->insertRow(col_index, value);
            col_index++;
            continue;
        }
    }
}

//===RUN==
int System::run()
{
    cout << "Welcome to Project Database. Please enter command:" << endl;
    char *command = new char[MAX_COMMAND_SIZE];
    char *filename = new char[MAX_FILENAME_SIZE];
    char *tablename = new char[MAX_TABLENAME_SIZE];
    char *value_input = new char[MAX_ROW_VALUE_LENGTH];

    cin >> filename;
    importTable(filename);
    command[0] = 'z';
    while ((strcmp(command, "close") != 0))
    {
        cin >> command;
        /*adds inputted filename's table to current database*/
        if (strcmp(command, "import") == 0)
        {
            cin >> filename;
            importTable(filename);
        }
        /*saves loaded tables to the files they were opened from*/
        if (strcmp(command, "save") == 0)
        {
            int size_loaded_tables = m_database->getSizeDatabase();
            for (int i = 0; i < size_loaded_tables; i++)
            {
                filename = m_database->getTableAtIndex(i)->getFilename();
                saveas(filename, *m_database->getTableAtIndex(i));
            }
            cout << "Succesfully saved loaded tables to their files." << endl;
            saveDatabase("database.info");
        }
        /*saves all loaded tables in one file with <filename>*/
        if (strcmp(command, "saveas") == 0)
        {
            cin >> filename;
            save_as_for_loaded_tables(filename);
            saveDatabase("database.info");
        }

        if (strcmp(command, "showtables") == 0)
        {
            showtables();
        }
        if (strcmp(command, "describe") == 0)
        {
            cin >> tablename;
            if (getOpenedTableByName(tablename))
            {
                Table *to_decribe = getOpenedTableByName(tablename);
                to_decribe->describe();
            }
            //Table *to_decribe = getOpenedTableByName(tablename);
            //to_decribe->describe();
        }
        if (strcmp(command, "print") == 0)
        {
            cin >> tablename;
            if (getOpenedTableByName(tablename))
            {
                Table *to_decribe = getOpenedTableByName(tablename);
                to_decribe->print();
            }
        }
        if (strcmp(command, "export") == 0)
        {
            cin >> tablename;
            cin >> filename;
            const char *filename_to_export = filename;
            if (getOpenedTableByName(tablename))
            {
                Table *table_to_save = getOpenedTableByName(tablename);
                saveas(filename_to_export, *table_to_save);
            }
        }
        if (strcmp(command, "select") == 0)
        {
            int column_n;
            cin >> column_n;
            cin >> value_input;
            cin >> tablename;
            select(column_n, value_input, tablename);
        }
        if (strcmp(command, "addcolumn") == 0)
        {
            cin >> tablename;
            char *column_name = new char[MAX_COLUMN_NAME];
            cin >> column_name;
            char *column_type = new char[MAX_TYPENAME_LENGTH];
            cin >> column_type;
            if (getOpenedTableByName(tablename))
            {
                Table *table_to_add_column = getOpenedTableByName(tablename);
                table_to_add_column->addColumnToExistingTable(column_name, column_type);
            }
        }
        if (strcmp(command, "update") == 0)
        {
            cin >> tablename;
            int search_column_n;
            cin >> search_column_n;
            cin >> value_input;
            int target_column_n;
            cin >> target_column_n;
            char *target_value_input = new char[MAX_ROW_VALUE_LENGTH];
            cin >> target_value_input;
            update(tablename, search_column_n, value_input, target_column_n, target_value_input);
        }
        if (strcmp(command, "delete") == 0)
        {
            cin >> tablename;
            int search_column_n;
            cin >> search_column_n;
            cin >> value_input;
            Delete(tablename, search_column_n, value_input);
        }
        if (strcmp(command, "insert") == 0)
        {
            cin >> tablename;

            insert(tablename, value_input);
        }
        if (strcmp(command, "innerjoin") == 0)
        {
            cin >> tablename;
            int column1;
            cin >> column1;
            char *tablename_second = new char[MAX_TABLENAME_SIZE];
            cin >> tablename_second;
            int column2;
            cin >> column2;
            innerjoin(tablename, column1, tablename_second, column2);
        }
        if (strcmp(command, "rename") == 0)
        {
            char *old_tablename = new char[MAX_TABLENAME_SIZE];
            cin >> old_tablename;
            char *new_tablename = new char[MAX_TABLENAME_SIZE];
            cin >> new_tablename;
            if (getOpenedTableByName(tablename))
            {
                Table *table_to_rename = getOpenedTableByName(old_tablename);
                table_to_rename->rename(new_tablename);
            }
        }
        if (strcmp(command, "count") == 0)
        {
            cin >> tablename;
            int search_column_n;
            cin >> search_column_n;
            cin >> value_input;
            count(tablename, search_column_n, value_input);
        }
        if (strcmp(command, "aggregate") == 0)
        {
            cin >> tablename;
            int search_column_n;
            cin >> search_column_n;
            cin >> value_input;
            int target_column_n;
            cin >> target_column_n;
            char *operation = new char[MAX_OPERATION_SIZE];
            cin >> operation;
            aggregate(tablename, search_column_n, value_input, target_column_n, operation);
        }
        if (strcmp(command, "exit") == 0)
        {
            cout << "Thank you for using Database! See you again." << endl;
            return 0;
        }
    }
    cout << "Closing all tables. All data that is not saved will be lost!" << endl;

    return 1;
}