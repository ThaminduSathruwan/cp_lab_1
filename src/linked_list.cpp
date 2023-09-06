#include <iostream>
#include <ctime>
#include <unordered_set>
#include <pthread.h>
#include "linked_list.h"

void LinkedList::Populate(int n, int mInsert, int mDelete,
                          std::unordered_set<int> &insertVals, std::unordered_set<int> &deleteVals)
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    std::unordered_set<int> uniqueVals;

    // Generate n unique values using random number generator
    while (uniqueVals.size() < (std::size_t)n)
    {
        int data = std::rand() % (1 << 16);
        uniqueVals.insert(data);
    }

    // Populate linked list with unique values
    Node *curr = head;
    Node *next = nullptr;
    for (auto it = uniqueVals.begin(); it != uniqueVals.end(); ++it)
    {
        next = new Node;
        next->data = *it;
        next->next = nullptr;
        if (curr == nullptr)
        {
            head = next;
        }
        else
        {
            curr->next = next;
        }
        curr = next;
        length++;
        std::cout << "Inserting " << *it << std::endl;
    }

    // Generate numbers to delete that are already in the linked list
    while (deleteVals.size() < (std::size_t)(mDelete))
    {
        int data = std::rand() % (1 << 16);
        std::size_t size = uniqueVals.size();
        uniqueVals.erase(data);
        if (size != uniqueVals.size()) // if the set size not changed, then the value was in the set
            deleteVals.insert(data);
    }

    // Generate numbers to insert that are not already in the linked list
    while (insertVals.size() < (std::size_t)(mInsert))
    {
        int data = std::rand() % (1 << 16);
        std::size_t size = uniqueVals.size();
        uniqueVals.insert(data);
        if (size != uniqueVals.size()) // if the set size changed, then the value was unique
            insertVals.insert(data);
    }
}

void SerialLinkedList::Member()
{
    // TODO: Implement this
}

void SerialLinkedList::Insert(int data)
{
    // TODO: Implement this
}

void SerialLinkedList::Remove(int data)
{
    // TODO: Implement this
}

void MutexParallelLinkedList::Member()
{
    // TODO: Implement this
}

void MutexParallelLinkedList::Insert(int data)
{
    // TODO: Implement this
}

void MutexParallelLinkedList::Remove(int data)
{
    // TODO: Implement this
}

void RwLockParallelLinkedList::Member()
{
    // TODO: Implement this
}

void RwLockParallelLinkedList::Insert(int data)
{
    // TODO: Implement this
}

void RwLockParallelLinkedList::Remove(int data)
{
    // TODO: Implement this
}
