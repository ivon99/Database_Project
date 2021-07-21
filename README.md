# Database_Project
Repository for OOP course project "Database".

Project "Database"

Project "Database" implements a program supporting operations with simple databases.
A database consist of a series of tables, each table saved in its own file.
The database is then saved in a master file (catalogue), which contains a list of the tables in the given database, where each table is associated with its name and filename.

Supported data types:
The supported data types for the tables are whole numbers, rational numbers, string, and null.

The following commands are supported:
        
 = import <filename>: : adds table from file <filename> to the database\
 = close: closes currently opened file
 = save: saves the currently open file 
 = saveas <filename>: saves the currently opened tables in <file>
 = showtables: prints names of all loaded tables
 = describe <name>: prints the type for every column in table <name>
 = print <name>: prints table
 = export <name> <file name>: saves table in file with <filename>
 = select <column-n> <value> <tablename>: prints all rows from given table that contain <value>
 = addcolumn <table name> <column name> <column type>: adds a new column of <column type>\n"
 = update <table name> <search column n> <search value> <target column n> <target value>: updates all rows in <target column> which have the <search value> in <search column>
 = insert <table name> <column1> ... <column n>: adds new row and inserts <value> at <serach column>
 = delete <table name> <searc column> <search value>: deletes value in <search column>
 = innerjoin <table1> <column1> <table2> <column 2>: innerjoins columns and produces a new table
 = rename <old name> <new name>: renames table
 = count <table name> <search column> <search value>: counts all rows whose column has <search value>
 = aggregate <table name> <search column> <search value> <target column> <operaton>: performs <operation> in <target column> on all rows which columns have <search calue>; supported operations are: sum, product, maximum, minimum"
 = help: prints methods information
