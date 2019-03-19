//
// Created by Joseph Fergen on 3/16/2019.
//

//Very similar to that of Table1 class
#ifndef INC_2110PROJECT2_TABLE2_H
#define INC_2110PROJECT2_TABLE2_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

struct itemScheme
{
    int ID = -1;
    string name;
    string type;
    string rarity;
    string price;
};

class Table2
{
public:
    Table2();
    void SetTableName(string t);
    void SetKey(int k);
    void SetItemID(int ID);
    void SetSchemeData(istringstream& dataHelp);
    void InsertData(istringstream& dataHelp);
    bool IsEmpty(int p);
    void DisplayItems();
    string GetTableName();
private:
    string tableName; // Name of the table (items)
    int key;
    itemScheme dataEntry;
    vector<itemScheme> hashTableItem;
};
#endif //INC_2110PROJECT2_TABLE2_H
