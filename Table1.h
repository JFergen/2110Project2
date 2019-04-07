//
// Created by Joseph Fergen on 3/16/2019.
//

#ifndef INC_2110PROJECT2_TABLE1_H
#define INC_2110PROJECT2_TABLE1_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

struct spellScheme
{
    string name = "";
    string level;
    string school;
    string castTime;
    string range;
    string components;
    string duration;
};

class Table1
{
public:
    Table1(); // Constructor that sets everything to 0 and sets base size
    void SetTableName(string t);
    void SetKey(string k); // Sets what is needed for the key
    void SetSpellName(string n);
    void SetSchemeData(istringstream& dataHelp); // Using a string stream of '|' delimited items, inputs data into struct
    bool InsertData(istringstream& dataHelp); // Inserts the data into the hash table
    bool UpdateData(istringstream& dataHelp); // Updates the data in the hash table
    void SelectData(istringstream& dataHelp); // Selects and returns data if found
    void DeleteData(istringstream& dataHelp); // Selects and returns data if found
    void WriteData(); // Writes out the data to an output file
    bool IsEmpty(int p); // Checks if the value in hash table is empty (can be empty from start or removed)
    void DisplaySpells();
    string GetTableName();
private:
    string tableName; // Name of the table (spells)
    string key;
    spellScheme dataEntry; // Data that goes into hash table
    vector<spellScheme> hashTableSpell; // Hash table
};

#endif //INC_2110PROJECT2_TABLE1_H
