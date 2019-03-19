//
// Created by Joseph Fergen on 3/16/2019.
//

#include "Table3.h"
#include "LinkedList3.h"

int CHARSIZE = 10; // Global int for the size of the hash table
LinkedList3 secIndexCust;

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

void Table3::InsertData(istringstream& dataHelp) //TODO Secondary INDEX
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
    pos = HashModulo2(key);//MidSqHash(key, R); // Getting position using Mid-Square Hashing TODO

    while(probed < hashTableChar.size()) // Double Hashing
    {
        if(IsEmpty(pos)) // Checks to see if it is empty using function
        {
            hashTableChar.at(pos) = dataEntry;
            //secIndexCust.Insert(dataEntry);
            break;
        }
        probed++; // Collision

        pos = (pos + 1) % hashTableChar.size();//((MidSqHash(key) + (HashModulo(key) * probed)) % hashTableChar.size());

        if(probed == hashTableChar.size()) //TODO If size is increased, must rehash everything
        {
            CHARSIZE = (CHARSIZE*2);
            break;
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

int MidSqHash(int key, int RCeil) // TODO
{
    int pos = key^2;
  //  string spos = static_cast<string>(pos);
  return -1;
}

int HashModulo2(int key)
{
    return (key % CHARSIZE);
}