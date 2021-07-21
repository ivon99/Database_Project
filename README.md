# Database_Project
Repository for OOP course project "Database".

**Project "Database"**

Project "Database" implements a program supporting operations with simple databases.
A database consist of a series of tables, each table saved in its own file.
The database is then saved in a master file (catalogue), which contains a list of the tables in the given database, where each table is associated with its name and filename.

**Supported data types:**\
The supported data types for the tables are whole numbers, rational numbers, string, and null.

**Commands:**
The following commands are supported:\
        = **import** : adds table from file filenameto the database\
        = **close** : closes currently opened file\
        = **save**: saves the currently open file \
        = **saveas**: saves the currently opened tables in file\
        = **showtables**: prints names of all loaded tables\
        = **describe**: prints the type for every column in table name\
        = **print**: prints table\
        = **export**: saves table in file with filename\
        = **select** : prints all rows from given table that contain value\
        = **addcolumn** : adds a new column of column type\
        = **update** : updates all rows in target column which have the search value in search column\
        = **insert** : adds new row and inserts value at serach column\
        = **delete**: deletes value in search column\
        = **innerjoin**: innerjoins columns and produces a new table\
        = **rename**: renames table\
        = **count** : counts all rows whose column has search value\
        = **aggregate**: performs  operation in target column on all rows which columns have search value; supported operations are: sum, product, maximum, minimum"\
        = **help**: prints methods information
