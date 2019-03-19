//
// Created by Joseph Fergen on 3/19/2019.
//

#ifndef INC_2110PROJECT2_LINKEDLIST2_H
#define INC_2110PROJECT2_LINKEDLIST2_H
#include "Table2.h"

struct node
{
    itemScheme data;
    node* next;
    int key = data.ID;
};

class LinkedList2
{
private:
    node* head;
    node* tail;
public:
    LinkedList2();
    void Insert(itemScheme info);
    bool Delete(int k);
};

#endif //INC_2110PROJECT2_LINKEDLIST2_H
