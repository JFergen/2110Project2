//
// Created by Joseph Fergen on 3/19/2019.
//

#ifndef INC_2110PROJECT2_LINKEDLIST_H
#define INC_2110PROJECT2_LINKEDLIST_H
#include "Table1.h"

struct node
{
    spellScheme* data;
    node* next;
};

class LinkedList1
{
private:
    node* head;
public:
    LinkedList1();
    void Insert(spellScheme &info);
    bool Delete(string k);
};

#endif //INC_2110PROJECT2_LINKEDLIST_H
