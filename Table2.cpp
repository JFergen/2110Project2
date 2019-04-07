//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table2.h"

int ITEMSIZE = 500; // Global int for the size of the hash table
list <itemScheme*> secIndexItem; // Secondary Index

int HashModulo(int key); // Regular modulo hashing function

Table2::Table2()
{
    tableName = "";
    key = -1;
    hashTableItem.resize(ITEMSIZE);
}

void Table2::SetTableName(string n)
{
    tableName = n;
}

void Table2::SetKey(int k)
{
    key = k;
}

void Table2::SetItemID(int ID)
{
    dataEntry.ID = ID;
}

void Table2::SetSchemeData(istringstream& dataHelp) // Sets the data for the struct before inserting into Hash Table
{
    string data;

    for(int i = 0; i < 4; i++)
    {
        getline(dataHelp, data, '|');

        switch (i)
        {
            case 0:
                dataEntry.name = data;
                break;
            case 1:
                dataEntry.type = data;
                break;
            case 2:
                dataEntry.rarity = data;
                break;
            case 3:
                dataEntry.price = data;
                break;
            default:
                return;
        }
    }
}

bool Table2::InsertData(istringstream& dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;

    getline(dataHelp, data, '|');

    int keyData = stoi(data);
    SetKey(keyData);
    SetItemID(keyData);

    SetSchemeData(dataHelp);

    pos = HashModulo(key); // Getting position using regular modulo hashing

    while(probed < hashTableItem.size()) // Quadratic probing
    {
        if(hashTableItem.at(pos).ID == dataEntry.ID) // If ID is already taken
        {
            return false;
        }

        if(IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableItem.at(pos) = dataEntry; // Primary index
            secIndexItem.push_back(&hashTableItem.at(pos));// Secondary index pointing to primary index
            return true;
        }
        probed++; // Collision

        pos = ((HashModulo(key) + (2 * probed) + 3 * (probed * probed)) % hashTableItem.size());
    }
    return false;
}

bool Table2::UpdateData(istringstream &dataHelp)
{
    string data;
    int pos = 0;
    int probed = 0;

    getline(dataHelp, data, '|');

    int keyData = stoi(data);
    SetKey(keyData);
    SetItemID(keyData);

    SetSchemeData(dataHelp);

    pos = HashModulo(key); // Getting position using regular modulo hashing

    while (probed < hashTableItem.size())
    {
        if(hashTableItem.at(pos).ID == dataEntry.ID) // If ID matches
        {
            hashTableItem.at(pos) = dataEntry;
            return true;
        }

        if (IsEmpty(pos)) // Checks to see if it is empty using function
        {
            return false;
        }
        probed++; // Collision
        pos = ((HashModulo(key) + (2 * probed) + 3 * (probed * probed)) % hashTableItem.size());
    }
}

void Table2::SelectData(istringstream &dataHelp)
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetSchemeData(dataHelp);

    if(data != "*")
    {
        int keyData = stoi(data);
        SetKey(keyData);
        SetItemID(keyData);
    }

    if (data == "*")
    {
        for (auto it = secIndexItem.begin(); it != secIndexItem.end(); it++)
        {
            if((dataEntry.name == (*it)->name) || (dataEntry.name == "*"))
            {
                if((dataEntry.name == (*it)->name) || (dataEntry.name == "*"))
                {
                    if((dataEntry.type == (*it)->type) || (dataEntry.rarity == "*"))
                    {
                        if((dataEntry.price == (*it)->price || dataEntry.price == "*"))
                        {
                            if((dataEntry.price == (*it)->price) || (dataEntry.price == "*"))
                            {
                                found = true;
                                cout << "Found (" << (*it)->ID << "|" << (*it)->name << "|" << (*it)->type << "|"
                                     << (*it)->rarity << "|" << (*it)->price << ")" << endl;
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
        pos = HashModulo(key); // Gets first position using string multiplicative hashing

        while (probed < hashTableItem.size()) {
            if (dataEntry.ID == hashTableItem.at(pos).ID) {
                cout << "Found (" << hashTableItem.at(pos).ID << "|" << hashTableItem.at(pos).name << "|"
                     << hashTableItem.at(pos).type << "|" << hashTableItem.at(pos).rarity << "|"
                     << hashTableItem.at(pos).price << ") in spells" << endl;
                return;
            }

            if (hashTableItem.at(pos).name.empty()) {
                cout << "No entries match query (" << printStuff << ")" << endl;
                return;
            }
            probed++; // Collision
            pos = ((HashModulo(key) + (2 * probed) + 3 * (probed * probed)) % hashTableItem.size());
        }
    }
}

void Table2::DeleteData(istringstream &dataHelp)
{
    string printStuff = dataHelp.str();
    string data;
    int pos = 0;
    int probed = 0;
    bool found = false;

    getline(dataHelp, data, '|');

    SetSchemeData(dataHelp);

    if(data != "*")
    {
        int keyData = stoi(data);
        SetKey(keyData);
        SetItemID(keyData);
    }

    if (data == "*")
    {
        for (auto it = secIndexItem.begin(); it != secIndexItem.end(); it++)
        {
            if ((dataEntry.name == (*it)->name) || (dataEntry.name == "*"))
            {
                if ((dataEntry.type == (*it)->type) || (dataEntry.type == "*"))
                {
                    if ((dataEntry.rarity == (*it)->rarity || dataEntry.rarity == "*"))
                    {
                        if ((dataEntry.price == (*it)->price) || (dataEntry.price == "*"))
                        {
                            found = true;
                            cout << "Deleted (" << (*it)->ID << "|" << (*it)->name << "|" << (*it)->type << "|"
                                 << (*it)->rarity << "|" << (*it)->price << ")" << endl;

                            hashTableItem.at(pos).ID = -2;
                            hashTableItem.at(pos).name = "removed";
                            hashTableItem.at(pos).type = "removed";
                            hashTableItem.at(pos).rarity = "removed";
                            hashTableItem.at(pos).price = "removed";
                        }
                    }
                }
            }
        }

        if (!found)
        {
            cout << "Failed to delete (" << printStuff << ")" << endl;
            return;
        }
        return;
    } else
    {
        pos = HashModulo(key); // Gets first position using string multiplicative hashing

        while (probed < hashTableItem.size())
        {
            if (dataEntry.ID == hashTableItem.at(pos).ID)
            {
                cout << "Deleted (" << hashTableItem.at(pos).ID << "|" << hashTableItem.at(pos).name << "|"
                     << hashTableItem.at(pos).type << "|" << hashTableItem.at(pos).rarity << "|"
                     << hashTableItem.at(pos).price << ") in items" << endl;

                hashTableItem.at(pos).ID = -2;
                hashTableItem.at(pos).name = "removed";
                hashTableItem.at(pos).type = "removed";
                hashTableItem.at(pos).rarity = "removed";
                hashTableItem.at(pos).price = "removed";
                return;
            }

            if (hashTableItem.at(pos).name.empty())
            {
                cout << "Failed to Delete (" << printStuff << ")" << endl;
                return;
            }
            probed++; // Collision
            pos = ((HashModulo(key) + (2 * probed) + 3 * (probed * probed)) % hashTableItem.size());
        }
    }
}

void Table2::WriteData()
{
    ofstream fout;

    fout.open("itemOutput.txt");

    fout << "ID" << endl;
    fout << "ID,NAME,TYPE,RARITY,PRICE" << endl;

    for (auto it = secIndexItem.begin(); it != secIndexItem.end(); it++)
    {
        if(((*it)->ID != -1) && ((*it)->ID != -2))
        {
            fout << (*it)->ID << "|" << (*it)->name << "|" << (*it)->type << "|" << (*it)->rarity << "|"
                 << (*it)->price << endl;
        }
    }
}

int HashModulo(int key)
{
    return (key % ITEMSIZE);
}

bool Table2::IsEmpty(int p)
{
    if(hashTableItem.at(p).ID == -1 || hashTableItem.at(p).ID == -2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Table2::DisplayItems()
{
    cout << setw(4) << "ID" << setw(20) << "NAME" << setw(14) << "TYPE" << setw(10) << "RARITY" << setw(6) << "PRICE"
    << endl;

    for(int i = 0; i < hashTableItem.size(); i++)
    {
        if(!IsEmpty(i))
        {
            cout << setw(4) << hashTableItem.at(i).ID << setw(20) << hashTableItem.at(i).name << setw(14)
                 << hashTableItem.at(i).type << setw(10) << hashTableItem.at(i).rarity << setw(6)
                 << hashTableItem.at(i).price << endl;
        }
    }
}

string Table2::GetTableName()
{
    return tableName;
}