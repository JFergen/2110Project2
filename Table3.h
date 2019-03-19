//
// Created by Joseph Fergen on 3/16/2019.
//

//Similar to table1 and table2
#ifndef INC_2110PROJECT2_TABLE3_H
#define INC_2110PROJECT2_TABLE3_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

struct charScheme
{
    int ID = -1;
    string name;
    string race;
    string level;
    string clas;
    string debt;
};

class Table3
{
public:
    Table3(); // Constructor that sets everything to 0 and sets base size
    void SetTableName(string t);
    void SetKey(int k); // Sets what is needed for the key
    void SetCharID(int ID);
    void SetSchemeData(istringstream& dataHelp); // Using a string stream of '|' delimited items, inputs data into struct
    void InsertData(istringstream& dataHelp); // Inserts the data into the hash table
    bool IsEmpty(int p); // Checks if the value in hash table is empty (can be empty from start or removed)
    void DisplayCharacters();
    string GetTableName();
private:
    string tableName; // Name of the table (characters)
    int key;
    charScheme dataEntry; // Data that goes into hash table
    vector<charScheme> hashTableChar; // Hash table
};

#endif //INC_2110PROJECT2_TABLE3_H
