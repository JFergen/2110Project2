//
// Created by Joseph Fergen on 3/16/2019.
//

#ifndef INC_2110PROJECT2_TABLE1_H
#define INC_2110PROJECT2_TABLE1_H

#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct spellScheme
{
    string name;
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
    Table1();
    void SetTableName(string t);
    void SetKey(string k);
    void SetSpellName(string n);
    void SetSchemeData(istringstream& dataHelp);
    void InsertData(istringstream& dataHelp);
    string GetTableName();
private:
    string tableName; // Name of the table (spells)
    string key;
    spellScheme dataEntry;
    vector<spellScheme> hashTableSpell;
};

#endif //INC_2110PROJECT2_TABLE1_H
