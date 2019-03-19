//
// Created by josep on 3/19/2019.
//

#include "LinkedList3.h"

LinkedList3::LinkedList3()
{
    head = nullptr;
    tail = nullptr;
}

void LinkedList3::Insert(charScheme info)
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

bool LinkedList3::Delete(int k)
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