//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table1.h"

int SPELLSIZE = 500; // Global int for the size of the hash table
list <spellScheme*> secIndexSpell;

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

bool Table1::InsertData(istringstream& dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);

    SetSchemeData(dataHelp);

    pos = StringHash(key); // Gets first position using string multiplicative hashing

    while (probed < hashTableSpell.size()) // Continues until it goes through whole hash table (Linear Probing)
    {
        if(hashTableSpell.at(pos).name == dataEntry.name) // If ID is already taken
        {
            return false;
        }

        if (IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableSpell.at(pos) = dataEntry; // Sets data into hash table (Primary Index)
            secIndexSpell.push_back(&hashTableSpell.at(pos));// Sec index to the primary index
            return true;
        }
        pos = (pos + 1) % hashTableSpell.size(); // Moves position one up
        probed++;
    }
    return false;
}

bool Table1::UpdateData(istringstream &dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);

    SetSchemeData(dataHelp);

    pos = StringHash(key); // Gets first position using string multiplicative hashing

    while (probed < hashTableSpell.size()) // Continues until it goes through whole hash table (Linear Probing)
    {
        if(hashTableSpell.at(pos).name == dataEntry.name) // If ID matches
        {
            hashTableSpell.at(pos) = dataEntry;
            return true;
        }

        if (IsEmpty(pos)) // Checks to see if it is empty using function
        {
            return false;
        }
        pos = (pos + 1) % hashTableSpell.size(); // Moves position one up
        probed++;
    }
}

void Table1::SelectData(istringstream &dataHelp)
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);

    SetSchemeData(dataHelp);

    pos = StringHash(key); // Gets first position using string multiplicative hashing

    if(dataEntry.name != "*")
    {
       while(probed < hashTableSpell.size())
        {
            if(dataEntry.name == hashTableSpell.at(pos).name)
            {
                cout << "Found (" << hashTableSpell.at(pos).name << "|" << hashTableSpell.at(pos).level << "|"
                    << hashTableSpell.at(pos).school << "|" << hashTableSpell.at(pos).castTime << "|"
                    << hashTableSpell.at(pos).range << "|" << hashTableSpell.at(pos).components << "|"
                    << hashTableSpell.at(pos).duration << ") in spells" << endl;
                return;
            }

            if(hashTableSpell.at(pos).name.empty())
            {
                cout << "No entries match query (" << printStuff << ")" << endl;
                return;
            }
            pos = (pos + 1) % hashTableSpell.size(); // Moves position one up
            probed++;
        }
        cout << "No entries match query (" << printStuff << ")" << endl;
        return;
    } else
    {
        for (auto it = secIndexSpell.begin(); it != secIndexSpell.end(); it++)
        {
            if((dataEntry.level == (*it)->level) || (dataEntry.level == "*"))
            {
                if((dataEntry.school == (*it)->school) || (dataEntry.school == "*"))
                {
                    if((dataEntry.castTime == (*it)->castTime) || (dataEntry.castTime == "*"))
                    {
                        if((dataEntry.range == (*it)->range || dataEntry.range == "*"))
                        {
                            if((dataEntry.components == (*it)->components) || (dataEntry.components == "*"))
                            {
                                if((dataEntry.duration == (*it)->duration) || (dataEntry.duration == "*"))
                                {
                                    found = true;
                                    cout << "Found (" << (*it)->name << "|" << (*it)->level << "|" << (*it)->school
                                    << "|" << (*it)->castTime << "|" << (*it)->range << "|" << (*it)->components
                                    << (*it)->duration << ")" << endl;
                                }
                             }
                        }
                    }
                }
            }
        }

        if(!found)
        {
            cout << "No entries match query (" << printStuff << ")" << endl;
            return;
        }
    }
}

void Table1::DeleteData(istringstream& dataHelp) // Selects and returns data if found
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetKey(data);
    SetSpellName(data);

    SetSchemeData(dataHelp);

    pos = StringHash(key); // Gets first position using string multiplicative hashing

    if(dataEntry.name != "*")
    {
        while(probed < hashTableSpell.size())
        {
            if(dataEntry.name == hashTableSpell.at(pos).name)
            {
                cout << "Deleted (" << hashTableSpell.at(pos).name << "|" << hashTableSpell.at(pos).level << "|"
                     << hashTableSpell.at(pos).school << "|" << hashTableSpell.at(pos).castTime << "|"
                     << hashTableSpell.at(pos).range << "|" << hashTableSpell.at(pos).components << "|"
                     << hashTableSpell.at(pos).duration << ") in spells" << endl;

                hashTableSpell.at(pos).name = "removed";
                hashTableSpell.at(pos).level = "removed";
                hashTableSpell.at(pos).school = "removed";
                hashTableSpell.at(pos).castTime = "removed";
                hashTableSpell.at(pos).range = "removed";
                hashTableSpell.at(pos).components = "removed";
                hashTableSpell.at(pos).duration = "removed";
                return;
            }

            if(hashTableSpell.at(pos).name.empty())
            {
                cout << "Failed to delete (" << printStuff << ")" << endl;
                return;
            }
            pos = (pos + 1) % hashTableSpell.size(); // Moves position one up
            probed++;
        }
        cout << "Failed to delete (" << printStuff << ")" << endl;
        return;
    } else
    {
        for (auto it = secIndexSpell.begin(); it != secIndexSpell.end(); it++)
        {
            if((dataEntry.level == (*it)->level) || (dataEntry.level == "*"))
            {
                if((dataEntry.school == (*it)->school) || (dataEntry.school == "*"))
                {
                    if((dataEntry.castTime == (*it)->castTime) || (dataEntry.castTime == "*"))
                    {
                        if((dataEntry.range == (*it)->range || dataEntry.range == "*"))
                        {
                            if((dataEntry.components == (*it)->components) || (dataEntry.components == "*"))
                            {
                                if((dataEntry.duration == (*it)->duration) || (dataEntry.duration == "*"))
                                {
                                    found = true;
                                    cout << "Deleted (" << (*it)->name << "|" << (*it)->level << "|" << (*it)->school
                                         << "|" << (*it)->castTime << "|" << (*it)->range << "|" << (*it)->components
                                         << (*it)->duration << ")" << endl;

                                    hashTableSpell.at(pos).name = "removed";
                                    hashTableSpell.at(pos).level = "removed";
                                    hashTableSpell.at(pos).school = "removed";
                                    hashTableSpell.at(pos).castTime = "removed";
                                    hashTableSpell.at(pos).range = "removed";
                                    hashTableSpell.at(pos).components = "removed";
                                    hashTableSpell.at(pos).duration = "removed";
                                }
                            }
                        }
                    }
                }
            }
        }

        if(!found)
        {
            cout << "Failed to delete (" << printStuff << ")" << endl;
            return;
        }
    }
}

void Table1::WriteData()
{
    ofstream fout;

    fout.open("spellsOutput.txt");

    fout << "NAME" << endl;
    fout << "NAME,LEVEL,SCHOOL,CASTING_TIME,RANGE,COMPONENTS,DURATION" << endl;

    for (auto it = secIndexSpell.begin(); it != secIndexSpell.end(); it++)
    {
        if(((*it)->name != "removed") && (!(*it)->name.empty()))
        {
            fout << (*it)->name << "|" << (*it)->level << "|" << (*it)->school << "|" << (*it)->castTime << "|"
                 << (*it)->range << "|" << (*it)->components << "|" << (*it)->duration << endl;
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
    if(hashTableSpell.at(p).name == "removed" || hashTableSpell.at(p).name.empty())
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