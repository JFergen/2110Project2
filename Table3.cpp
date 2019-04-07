//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table3.h"

int CHARSIZE = 500; // Global int for the size of the hash table
list <charScheme*> secIndexCust;

int MidSqHash(int key, int RCeil); // Hashing using Mid-Square Hash (base 10)
int HashModulo2(int key); // Regular modulo hashing function

Table3::Table3()
{
    tableName = "";
    key = -1;
    hashTableChar.resize(CHARSIZE);
}

void Table3::SetTableName(string n)
{
    tableName = n;
}

void Table3::SetKey(int k)
{
    key = k;
}

void Table3::SetCharID(int ID)
{
    dataEntry.ID = ID;
}

void Table3::SetSchemeData(istringstream& dataHelp) // Sets the data for the struct before inserting into Hash Table
{
    string data;

    for(int i = 0; i < 5; i++)
    {
        getline(dataHelp, data, '|');

        switch (i)
        {
            case 0:
                dataEntry.name = data;
                break;
            case 1:
                dataEntry.race = data;
                break;
            case 2:
                dataEntry.level = data;
                break;
            case 3:
                dataEntry.clas = data;
                break;
            case 4:
                dataEntry.debt = data;
                break;
            default:
                return;
        }
    }
}

bool Table3::InsertData(istringstream& dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;
    int R = 0;

    getline(dataHelp, data, '|');

    int keyData = stoi(data);
    SetKey(keyData);
    SetCharID(keyData);

    SetSchemeData(dataHelp);

    R = ceil(log10(CHARSIZE));
    pos = MidSqHash(key, R); // Getting position using Mid-Square Hashing

    while(probed < hashTableChar.size()) // Double Hashing using Mid-Square and Modulo Hashing
    {
        if(hashTableChar.at(pos).ID == dataEntry.ID) // If ID is already taken
        {
            return false;
        }

        if(IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableChar.at(pos) = dataEntry; // Primary index
            secIndexCust.push_back(&hashTableChar.at(pos)); // Sec index pointing to primary index
            return true;
        }
        probed++; // Collision

        pos = ((MidSqHash(key, R) + (HashModulo2(key) * probed)) % hashTableChar.size());
    }
    return false;
}

bool Table3::UpdateData(istringstream &dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;
    int R = 0;

    getline(dataHelp, data, '|');

    int keyData = stoi(data);
    SetKey(keyData);
    SetCharID(keyData);

    SetSchemeData(dataHelp);

    R = ceil(log10(CHARSIZE));
    pos = MidSqHash(key, R); // Getting position using Mid-Square Hashing

    while (probed < hashTableChar.size())
    {
        if(hashTableChar.at(pos).ID == dataEntry.ID) // If ID matches
        {
            hashTableChar.at(pos) = dataEntry;
            return true;
        }

        if (IsEmpty(pos)) // Checks to see if it is empty using function
        {
            return false;
        }
        probed++; // Collision
        pos = ((MidSqHash(key, R) + (HashModulo2(key) * probed)) % hashTableChar.size());
    }
}

void Table3::SelectData(istringstream &dataHelp)
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    int R = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetSchemeData(dataHelp);

    if(data != "*")
    {
        int keyData = stoi(data);
        SetKey(keyData);
        SetCharID(keyData);
    }

    if (data == "*")
    {
        for (auto it = secIndexCust.begin(); it != secIndexCust.end(); it++)
        {
            if((dataEntry.name == (*it)->name) || (dataEntry.name == "*"))
            {
                if((dataEntry.race == (*it)->race) || (dataEntry.race == "*"))
                {
                    if((dataEntry.level == (*it)->level) || (dataEntry.level == "*"))
                    {
                        if((dataEntry.clas == (*it)->clas || dataEntry.clas == "*"))
                        {
                            if((dataEntry.debt == (*it)->debt) || (dataEntry.debt == "*"))
                            {
                                found = true;
                                cout << "Found (" << (*it)->ID << "|" << (*it)->name << "|" << (*it)->race << "|"
                                << (*it)->level << "|" << (*it)->clas << "|" << (*it)->debt << ")" << endl;
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
        return;
    } else
    {
        R = ceil(log10(CHARSIZE));
        pos = MidSqHash(key, R); // Getting position using Mid-Square Hashing

        while (probed < hashTableChar.size()) {
            if (dataEntry.ID == hashTableChar.at(pos).ID) {
                cout << "Found (" << hashTableChar.at(pos).ID << "|" << hashTableChar.at(pos).name << "|"
                     << hashTableChar.at(pos).race << "|" << hashTableChar.at(pos).level << "|"
                     << hashTableChar.at(pos).clas << "|" << ") in spells" << endl;
                return;
            }

            if (hashTableChar.at(pos).ID == -1) {
                cout << "No entries match query (" << printStuff << ")" << endl;
                return;
            }
            probed++; // Collision
            pos = ((MidSqHash(key, R) + (HashModulo2(key) * probed)) % hashTableChar.size());
        }
    }
}

void Table3::DeleteData(istringstream& dataHelp) // Selects and returns data if found
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    int R = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetSchemeData(dataHelp);

    if(data != "*")
    {
        int keyData = stoi(data);
        SetKey(keyData);
        SetCharID(keyData);
    }

    if (data == "*")
    {
        for (auto it = secIndexCust.begin(); it != secIndexCust.end(); it++)
        {
            if((dataEntry.name == (*it)->name) || (dataEntry.name == "*"))
            {
                if((dataEntry.race == (*it)->race) || (dataEntry.race == "*"))
                {
                    if((dataEntry.level == (*it)->level) || (dataEntry.level == "*"))
                    {
                        if((dataEntry.clas == (*it)->clas || dataEntry.clas == "*"))
                        {
                            if((dataEntry.debt == (*it)->debt) || (dataEntry.debt == "*"))
                            {
                                found = true;
                                cout << "Deleted (" << (*it)->ID << "|" << (*it)->name << "|" << (*it)->race << "|"
                                     << (*it)->level << "|" << (*it)->clas << "|" << (*it)->debt << ")" << endl;

                                hashTableChar.at(pos).ID = -2;
                                hashTableChar.at(pos).name = "removed";
                                hashTableChar.at(pos).race = "removed";
                                hashTableChar.at(pos).level = "removed";
                                hashTableChar.at(pos).clas = "removed";
                                hashTableChar.at(pos).debt = "removed";
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
        return;
    } else
    {
        R = ceil(log10(CHARSIZE));
        pos = MidSqHash(key, R); // Getting position using Mid-Square Hashing

        while (probed < hashTableChar.size())
        {
            if (dataEntry.ID == hashTableChar.at(pos).ID)
            {
                cout << "Deleted (" << hashTableChar.at(pos).ID << "|" << hashTableChar.at(pos).name << "|"
                     << hashTableChar.at(pos).race << "|" << hashTableChar.at(pos).level << "|"
                     << hashTableChar.at(pos).clas << "|" << hashTableChar.at(pos).debt << ") in customers" << endl;
                return;
            }

            if (hashTableChar.at(pos).ID == -1) {
                cout << "Failed to delete (" << printStuff << ")" << endl;
                return;
            }
            probed++; // Collision
            pos = ((MidSqHash(key, R) + (HashModulo2(key) * probed)) % hashTableChar.size());
        }
    }
}

void Table3::WriteData()
{
    ofstream fout;

    fout.open("custOutput.txt");

    fout << "ID" << endl;
    fout << "ID,NAME,RACE,LEVEL,CLASS,DEBT" << endl;

    for (auto it = secIndexCust.begin(); it != secIndexCust.end(); it++)
    {
        if(((*it)->ID != -1) && ((*it)->ID != -2))
        {
            fout << (*it)->ID << "|" << (*it)->name << "|" << (*it)->race << "|" << (*it)->level << "|"
                 << (*it)->clas << "|" << (*it)->debt << endl;
        }
    }
}

bool Table3::IsEmpty(int p)
{
    if(hashTableChar.at(p).ID == -1 || hashTableChar.at(p).ID == -2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Table3::DisplayCharacters()
{
    cout << setw(3) << "ID" << setw(18) << "NAME" << setw(9) << "RACE" << setw(6) << "LEVEL" << setw(8) << "CLASS"
         << setw(7) << "DEBT" << endl;

    for(int i = 0; i < hashTableChar.size(); i++)
    {
        if(!IsEmpty(i))
        {
            cout << setw(3) << hashTableChar.at(i).ID << setw(18) << hashTableChar.at(i).name << setw(9)
                 << hashTableChar.at(i).race << setw(6) << hashTableChar.at(i).level << setw(8)
                 << hashTableChar.at(i).clas<< setw(7) << hashTableChar.at(i).debt << endl;
        }
    }
}

string Table3::GetTableName()
{
    return tableName;
}

int MidSqHash(int key, int RCeil)
{
    int pos;
    pos = key ^ 2;
    string spos = to_string(pos);
    string mpos = spos.substr(floor(spos.size()/2), RCeil);

  return (stoi(mpos) % CHARSIZE);
}

int HashModulo2(int key)
{
    return (key % CHARSIZE);
}