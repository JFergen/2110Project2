//
// Created by Joseph Fergen on 3/19/2019.
//

#ifndef INC_2110PROJECT2_LINKEDLIST3_H
#define INC_2110PROJECT2_LINKEDLIST3_H
#include "Table3.h"

struct node
{
    charScheme data;
    node* next;
    int key = data.ID;
};

class LinkedList3
{
private:
    node* head;
    node* tail;
public:
    LinkedList3();
    void Insert(charScheme info);
    bool Delete(int k);
};
#endif //INC_2110PROJECT2_LINKEDLIST3_H
