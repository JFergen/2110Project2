//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table2.h"
#include "LinkedList2.h"

int ITEMSIZE = 10; // Global int for the size of the hash table
LinkedList2 secIndexItem; // Secondary Index

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

void Table2::InsertData(istringstream& dataHelp) //TODO Secondary INDEX
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
        if(IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableItem.at(pos) = dataEntry;
            secIndexItem.Insert(dataEntry);
            break;
        }
        probed++; // Collision

        pos = ((HashModulo(key) + (1 * probed) + 1 * (probed * probed)) % hashTableItem.size());

        if(probed == hashTableItem.size()) //TODO If size is increased, must rehash everything
        {
            ITEMSIZE = (ITEMSIZE*2);
            break;
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