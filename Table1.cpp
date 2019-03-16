//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table1.h"

int SPELLSIZE = 10; // Global int for the size of the hash table

int StringHash(string key);
bool IsEmpty(int p); // TODO: If I am removing something I need to set the name to "removed"

Table1::Table1()
{
    tableName = "";
    key = "";
    hashTableSpell.resize(SPELLSIZE);
}

void Table1::SetTableName(string t)
{
    tableName = t;
}

void Table1::SetKey(string k)
{
    key = k;
}

void Table1::SetSpellName(string n)
{
    dataEntry.name = n;
}

void Table1::SetSchemeData(istringstream& dataHelp) // Sets the data for the struct before inserting into Hash Table
{
    string data;

    for(int i = 0; i < 6; i++)
    {
        getline(dataHelp, data, '|');

        switch (i)
        {
            case 0:
                dataEntry.level = data;
                break;
            case 1:
                dataEntry.school = data;
                break;
            case 2:
                dataEntry.castTime = data;
                break;
            case 3:
                dataEntry.range = data;
                break;
            case 4:
                dataEntry.components = data;
                break;
            case 5:
                dataEntry.duration = data;
                break;
            default:
                return;
        }
    }
}

void Table1::InsertData(istringstream& dataHelp)
{
    string data;
    int pos;
    int probed = 0;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);
    SetSchemeData(dataHelp);

    pos = StringHash(key);

    while(probed < hashTableSpell.size())
    {
        if(IsEmpty(pos)) // Checks to see if it is empty using function
        probed++;

        if(probed == hashTableSpell.size())
        {
            SPELLSIZE = (SPELLSIZE*2);
        }
    }
}

string Table1::GetTableName()
{
    return tableName;
}

int StringHash(string key)
{
    int pos = 0;
    int mult = 2;

    for(char& c : key)
    {
        pos = (pos*mult) + c;
    }

    return (pos % SPELLSIZE);
}

bool IsEmpty(int p) // TODO
{

}