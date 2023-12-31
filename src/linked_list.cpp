#include <iostream>
#include <ctime>
#include <set>
#include <pthread.h>
#include "linked_list.h"

void LinkedList::Populate(int n)
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    std::set<int> uniqueVals;

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
    }
}

// Check if an element exists in the linked list
bool SerialLinkedList::Member(int data)
{
    Node *curr = head;

    while (curr != nullptr && curr->data <= data)
        curr = curr->next;

    return !(curr == nullptr || curr->data > data);
}

// Insert an element into the linked list
bool SerialLinkedList::Insert(int data)
{
    Node *curr = head;
    Node *prev = nullptr;
    Node *temp;

    while (curr != nullptr && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == nullptr || curr->data > data)
    {
        temp = new Node;
        temp->data = data;
        temp->next = curr;
        if (prev == nullptr)
        {
            head = temp;
        }
        else
        {
            prev->next = temp;
        }
        length++;
        return true;
    }
    return false;
}

// Remove an element from the linked list
bool SerialLinkedList::Remove(int data)
{
    Node *curr = head;
    Node *prev = nullptr;

    while (curr != nullptr && curr->data < data)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr && curr->data == data)
    {
        if (prev == nullptr)
        {
            head = curr->next;
        }
        else
        {
            prev->next = curr->next;
        }
        delete curr;
        length--;
        return true;
    }
    return false;
}

bool MutexParallelLinkedList::Member(int data)
{
    pthread_mutex_lock(&mutex);
    bool result = SerialLinkedList::Member(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

bool MutexParallelLinkedList::Insert(int data)
{
    pthread_mutex_lock(&mutex);
    bool result = SerialLinkedList::Insert(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

bool MutexParallelLinkedList::Remove(int data)
{
    pthread_mutex_lock(&mutex);
    bool result = SerialLinkedList::Remove(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

bool RwLockParallelLinkedList::Member(int data)
{
    pthread_rwlock_rdlock(&rwlock);
    bool result = SerialLinkedList::Member(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}

bool RwLockParallelLinkedList::Insert(int data)
{
    pthread_rwlock_wrlock(&rwlock);
    bool result = SerialLinkedList::Insert(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}

bool RwLockParallelLinkedList::Remove(int data)
{
    pthread_rwlock_wrlock(&rwlock);
    bool result = SerialLinkedList::Remove(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}
