#include "Table1.h"
#include "Table2.h"
#include "Table3.h"

void Display(); // Displays all of the tables
void Insert(const string &data, const string &table); // Inserts data into correct tables
void Update(const string &data, const string &table); // Updates data in correct tables
void Select(const string &data, const string &table); // Selects and returns data if found
void Delete(const string &data, const string &table); // Selects and deletes data if found
void Write(); // Writes data to separate output files
void CheckFunc(const string &func, const string &data = "", const string &tableName = ""); // Used to check which function to use from input file
int WhichTable(const string &t); // Used to decide which table to insert data to

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

                while (getline(finTable, parseHelp))
                {
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

    finMain.ignore();

    // Reads in the functions from input file and does necessary actions
    while(getline(finMain, parseHelp))
    {
        istringstream goAway(parseHelp); // Used to get rid of (( and ))
        string funcToDo;
        string dataToStore;
        string dataHelp;
        string tableN;
        char garbageChar;

        while(getline(goAway, funcToDo, '(')) // Gets rid of first '('
        {
            goAway.get(garbageChar);

            if(goAway.peek() == -1)//(garbageChar != ')') && (garbageChar != '\n'))
            {
                CheckFunc(funcToDo);
            } else
            {
                getline(goAway, dataToStore, ')'); // Gets tuple of data

                if(goAway.peek() != 44) // If there are more '(' in the data that need to be captured
                {
                    getline(goAway, dataHelp, ')');
                    dataToStore += ")";
                    dataToStore += dataHelp;
                }
                goAway.get(garbageChar); // Gets rid of ,
                getline(goAway, tableN, ')'); // Gets table name
                goAway.get(garbageChar);
                CheckFunc(funcToDo, dataToStore, tableN);
            }
        }
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

void Insert(const string &data, const string &table)
{
    istringstream dataHelp(data);

    if(table == "spells")
    {
        if(spellsTable.InsertData(dataHelp))
        {
            cout << "Inserted (" << data << ") into " << table << endl;
        } else
        {
            cout << "Failed to insert (" << data << ") into " << table << endl;
        }
    }
    else if(table == "items")
    {
        if(itemsTable.InsertData(dataHelp))
        {
            cout << "Inserted (" << data << ") into " << table << endl;
        } else
        {
            cout << "Failed to insert (" << data << ") into " << table << endl;
        }
    }
    else if(table == "customers")
    {
        if(charTable.InsertData(dataHelp))
        {
            cout << "Inserted (" << data << ") into " << table << endl;
        } else
        {
            cout << "Failed to insert (" << data << ") into " << table << endl;
        }
    }
}

void Update(const string &data, const string &table)
{
    istringstream dataHelp(data);

    if(table == "spells")
    {
        if(spellsTable.UpdateData(dataHelp))
        {
            cout << "Updated (" << data << ") in " << table << endl;
        } else
        {
            cout << "Failed to update (" << data << ") into " << table << endl;
        }
    }
    else if(table == "items")
    {
        if(itemsTable.UpdateData(dataHelp))
        {
            cout << "Updated (" << data << ") into " << table << endl;
        } else
        {
            cout << "Failed to update (" << data << ") into " << table << endl;
        }
    }
    else if(table == "customers")
    {
        if(charTable.UpdateData(dataHelp))
        {
            cout << "Updated (" << data << ") into " << table << endl;
        } else
        {
            cout << "Failed to update (" << data << ") into " << table << endl;
        }
    }
}

void Select(const string &data, const string &table)
{
    istringstream dataHelp(data);

    if(table == "spells")
    {
        spellsTable.SelectData(dataHelp);
    }
    else if(table == "items")
    {
        itemsTable.SelectData(dataHelp);
    }
    else if(table == "customers")
    {
        charTable.SelectData(dataHelp);
    }
}

void Delete(const string &data, const string &table)
{
    istringstream dataHelp(data);

    if(table == "spells")
    {
        spellsTable.DeleteData(dataHelp);
    }
    else if(table == "items")
    {
        itemsTable.DeleteData(dataHelp);
    }
    else if(table == "customers")
    {
        charTable.DeleteData(dataHelp);
    }
}

void Write()
{
    spellsTable.WriteData();
    itemsTable.WriteData();
    charTable.WriteData();
}

void CheckFunc(const string &func, const string &data, const string &tableName)
{
    if(func == "DISPLAY")
    {
        cout << endl;
        Display();
    }
    else if(func == "INSERT")
    {
        Insert(data, tableName);
    }
    else if(func == "UPDATE")
    {
        Update(data, tableName);
    }
    else if(func == "SELECT")
    {
        Select(data, tableName);
    }
    else if(func == "DELETE")
    {
        Delete(data, tableName);
    }
    else if(func == "WRITE")
    {
        Write();
    }
}

int WhichTable(const string &t)
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