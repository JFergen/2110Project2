#include "Table1.h"
#include "Table2.h"
#include "Table3.h"
#include <iostream>
#include <fstream>

int main() 
{
    string fileName;
    ifstream finMain; // Used to read the main input file
    ifstream finTable; // Used to read in the table files
    string tableName; // Storing name of each table
    string parseHelp;
    Table1 spellsTable;

    cout << "Enter filename containing list of dishes: ";  // Gets filename to open from user
    cin >> fileName;

    finMain.open(fileName.c_str()); // Opens main file for input

    finMain >> fileName;
    finMain >> tableName;

    //TABLE 1 INSERTING DATA
    finTable.open(fileName.c_str()); // Opens first table file for input
    spellsTable.SetTableName(tableName); // Sets name of the first table

    finTable >> parseHelp; // First gets the key
    spellsTable.SetKey(parseHelp); // Sets the key for the table

    getline(finTable, parseHelp); // Skip the 2nd line as we already know scheme

    while(!finTable.eof())
    {
        getline(finTable, parseHelp); // Gets each line of spells
        istringstream declassify(parseHelp); // Used to get rid of '|' from parseHelp
        spellsTable.InsertData(declassify);
    }

    finMain.close();

    return 0;
}