#include "Database.hpp"
#include <cstring>
#include <iostream>
using namespace std;

int Database::getSizeDatabase() const
{
    return m_database.getSize();
}

Table *Database::getTableAtIndex(int index) const
{
    return m_database[index];
}

Table *Database::getTable(const char *tablename) const
{
    int size_database = m_database.getSize();
    for (int i = 0; i < size_database; i++)
    {
        if (isTable(tablename))
        {
            return m_database[i];
        }
    }
    cout << "Unable to find a table with this tablename" << endl;
    tablename--;
    return nullptr;
}

bool Database::isTable(char *tablename) const
{
    int size = m_database.getSize();
    for (int i = 0; i < size; i++)
    {
        const char *this_name = m_database.getElement(i)->getName();
        if (strcmp(this_name, tablename) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Database::isTable(const char *tablename) const
{
    int size = m_database.getSize();
    for (int i = 0; i < size; i++)
    {
        const char *this_name = m_database.getElement(i)->getName();
        if (strcmp(this_name, tablename) == 0)
        {
            return true;
        }
    }
    return false;
}

void Database::addTable(Table *new_table)
{

    if (isTable(new_table->getName()))
    {
        cout << "Tablename already exists!" << endl;
        return;
    }
    else
    {
        m_database.addElement(new_table);
        cout << "Successfully imported table with name " << new_table->getName() << " to current database!" << endl;
        return;
    }
}

void saveDatabaseToFile(std::ofstream &outfile, Database &obj)
{
    int size = obj.m_database.getSize();
    outfile << "Database is:" << endl;
    for (int i = 0; i < size; i++)
    {
        outfile << obj.m_database[i]->getName() << " ";
        outfile << obj.m_database[i]->getFilename() << endl;
    }
}