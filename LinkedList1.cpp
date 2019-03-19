//
// Created by Joseph Fergen on 3/19/2019.
//

#include "LinkedList1.h"

LinkedList1::LinkedList1()
{
    head = nullptr;
    tail = nullptr;
}

void LinkedList1::Insert(spellScheme info)
{
    node *tmp = new node;
    tmp->data = info;
    tmp->next = nullptr;

    if(head == nullptr)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
}

bool LinkedList1::Delete(string k)
{
    node *curr;
    node *prev;
    prev = curr = head;

    while(curr != nullptr && curr->key != k)
    {
        prev = curr;
        curr = curr->next;
    }

    if(curr == nullptr)
    {
        return false;
    }

    if(curr == head)
    {
        head = head->next;
        return true;
    }
    else
    {
        prev->next = curr->next;
        if(curr->next == nullptr)
        {
            tail = prev;
        }
        delete(curr);

        return true;
    }
}