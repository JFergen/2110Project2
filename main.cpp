#include "Table1.h"
#include "Table2.h"
#include "Table3.h"
#include <fstream>

void Display(); // Displays all of the tables
void CheckFunc(char c); // Used to check which function to use from input file
int WhichTable(const string t); // Used to decide which table to insert data to

Table1 spellsTable; // Global table for spells
Table2 itemsTable; // Global table for items
Table3 charTable; // Global table for characters

int main() 
{
    string fileName; // Reads in filename from user as well as gets secondary file names
    ifstream finMain; // Used to read the main input file
    ifstream finTable; // Used to read in from the table files
    string tableName; // Storing name of each table
    string parseHelp;
    char firstLetter; // Used with CheckFunc function to declare which function to run from file
    int tableNum;

    cout << "Enter filename containing tables and data: ";  // Gets filename to open from user
    cin >> fileName;

    finMain.open(fileName.c_str()); // Opens main file for input

    for(int i = 0; i < 3; i++) // This runs 3 times to get all 3 tables filled out, order not dependent
    {
        finMain >> fileName; // Reads in the name of text file and name of table first
        finMain >> tableName;

        tableNum = WhichTable(tableName);

        finMain.ignore();

        switch (tableNum) {
            case 1:
                //TABLE 1 INSERTING DATA
                finTable.open(fileName.c_str()); // Opens first table file for input
                spellsTable.SetTableName(tableName); // Sets name of the first table

                getline(finTable, parseHelp);
                spellsTable.SetKey(parseHelp); // Sets the key for the table
                getline(finTable, parseHelp); // Skip the 2nd line as we already know scheme

                while (!finTable.eof()) {
                    getline(finTable, parseHelp); // Gets each line of spells
                    istringstream declassify(parseHelp); // Used to get rid of '|' from parseHelp
                    spellsTable.InsertData(declassify);
                }
                finTable.close(); //FINISHED WITH TABLE 1
                break;

            case 2:
                finTable.open(fileName.c_str()); // Opens second table file for input
                itemsTable.SetTableName(tableName); // Sets name of the second table

                getline(finTable, parseHelp);
                getline(finTable, parseHelp); // Skip the 2nd line as we already know scheme

                while(getline(finTable, parseHelp))
                {
                    istringstream declassify(parseHelp); // Used to get rid of '|' from parseHelp
                    itemsTable.InsertData(declassify);
                }
                finTable.close(); //FINISHED WITH TABLE 2
                break;

            case 3:
                finTable.open(fileName.c_str()); // Opens third table file for input
                charTable.SetTableName(tableName); // Sets name of the third table

                getline(finTable, parseHelp); // Skip the 2nd line as we already know scheme
                getline(finTable, parseHelp); // Skip the 2nd line as we already know scheme

                while(getline(finTable, parseHelp))
                {
                    istringstream declassify(parseHelp); // Used to get rid of '|' from parseHelp
                    charTable.InsertData(declassify);
                }
                finTable.close(); //FINISHED WITH TABLE 3
        }

    }

    // Reads in the functions from input file and does necessary actions
    while(finMain.get(firstLetter))
    {
        CheckFunc(firstLetter);
        getline(finMain, parseHelp); // Skips to next line
    }

    finMain.close();

    return 0;
}

void Display()
{
    spellsTable.DisplaySpells();
    cout << endl;

    itemsTable.DisplayItems();
    cout << endl;

    charTable.DisplayCharacters();
    cout << endl;
}

void CheckFunc(char c)
{
    switch (c)
    {
        case 'D':
            Display();
            break;
            //TODO FOR OTHER FUNCTIONS
        default:
            break;
    }
}

int WhichTable(const string t)
{
    if(t == "spells")
    {
        return 1;
    }
    if(t == "items")
    {
        return 2;
    }
    if(t == "customers")
    {
        return 3;
    }
}