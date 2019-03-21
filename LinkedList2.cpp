//
// Created by josep on 3/19/2019.
//

#include "LinkedList2.h"

LinkedList2::LinkedList2()
{
    head = nullptr;
}

void LinkedList2::Insert(itemScheme &info)
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

bool LinkedList2::Delete(int k) // TODO
{
    node *curr;
    node *prev;
    prev = curr = head;

    while(curr != nullptr)
    {
        prev = curr;
        curr = curr->next;
    }

    //if(curr == nullptr)
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

        }
        delete(curr);

        return true;
    }
}