//
// Created by Joseph Fergen on 3/19/2019.
//

#include "LinkedList1.h"

LinkedList1::LinkedList1()
{
    head = nullptr;
}

void LinkedList1::Insert(spellScheme &info)
{
    node* tmp = new node;

    if(head == nullptr)
    {
        tmp->data = &info;

        head = tmp;
        tmp->next = nullptr;
    }
    else
    {
        tmp->data = &info;
        tmp->next = nullptr;
        node* it;

        it = head;

        while(it->next != nullptr)
        {
            it = it->next;
        }
        it->next = tmp;
    }
}

bool LinkedList1::Delete(string k) //TODO
{
    node *curr;
    node *prev;
    prev = curr = head;

    while(curr != nullptr) //&& curr->key != k)
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
            //tail = prev;
        }
        delete(curr);

        return true;
    }
}