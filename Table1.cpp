//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table1.h"
#include "LinkedList1.h"

int SPELLSIZE = 10; // Global int for the size of the hash table
LinkedList1 secIndexSpell; // Secondary Index

int StringHash(string key); // String multiplicative hashing function

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

void Table1::InsertData(istringstream& dataHelp) //TODO Secondary INDEX
{
    string data;
    int pos = 0;
    int probed = 0;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);

    SetSchemeData(dataHelp);

    pos = StringHash(key); // Gets first position using string multiplicative hashing

    while(probed < hashTableSpell.size()) // Continues until it goes through whole hash table (Linear Probing)
    {
        if(IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableSpell.at(pos) = dataEntry; // Sets data into hash table (Primary Index)
            //secIndexSpell.Insert(dataEntry); // Sets data into secondary index
            break;
        }
        pos = (pos + 1) % hashTableSpell.size(); // Moves position one up
        probed++;

        if(probed == hashTableSpell.size()) //TODO If size is increased, must rehash everything
        {
            SPELLSIZE = (SPELLSIZE*2);
            break;
        }
    }
}

int StringHash(string key) // String multiplicative hashing
{
    int pos = 0;
    int mult = 2;

    for(char& c : key)
    {
        pos = (pos*mult) + c;
    }

    return (pos % SPELLSIZE);
}

bool Table1::IsEmpty(int p)
{
    if(hashTableSpell.at(p).name == "removed" || hashTableSpell.at(p).name == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Table1::DisplaySpells()
{
    cout << setw(17) << "NAME" << setw(6) << "LEVEL" << setw(14) << "SCHOOL" << setw(13) << "CASTING_TIME" << setw(9)
    << "RANGE" << setw(54) << "COMPONENTS" << setw(32) << "DURATION" << endl;

    for(int i = 0; i < hashTableSpell.size(); i++)
    {
        if(!IsEmpty(i))
        {
            cout << setw(17) << hashTableSpell.at(i).name << setw(6) << hashTableSpell.at(i).level << setw(14)
            << hashTableSpell.at(i).school << setw(13) << hashTableSpell.at(i).castTime << setw(9)
            << hashTableSpell.at(i).range << setw(54) << hashTableSpell.at(i).components << setw(32)
            << hashTableSpell.at(i).duration << endl;
        }
    }
}

string Table1::GetTableName()
{
    return tableName;
}