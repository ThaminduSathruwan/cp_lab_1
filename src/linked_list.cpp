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

// Check if an element exists in the linked list
int SerialLinkedList::Member(int data)
{
    Node *curr = head;

    while (curr != nullptr && curr->data <= data)
        curr = curr->next;

    if (curr == nullptr || curr->data > data)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Insert an element into the linked list
int SerialLinkedList::Insert(int data)
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
        return 1;
    }
    else
    {
        return 0;
    }
}

// Remove an element from the linked list
int SerialLinkedList::Remove(int data)
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
        return 1;
    }
    else
    {
        return 0;
    }
}

int MutexParallelLinkedList::Member(int data)
{
    pthread_mutex_lock(&mutex);
    int result = SerialLinkedList::Member(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

int MutexParallelLinkedList::Insert(int data)
{
    pthread_mutex_lock(&mutex);
    int result = SerialLinkedList::Insert(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

int MutexParallelLinkedList::Remove(int data)
{
    pthread_mutex_lock(&mutex);
    int result = SerialLinkedList::Remove(data);
    pthread_mutex_unlock(&mutex);
    return result;
}

int RwLockParallelLinkedList::Member(int data)
{
    pthread_rwlock_rdlock(&rwlock);
    int result = SerialLinkedList::Member(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}

int RwLockParallelLinkedList::Insert(int data)
{
    pthread_rwlock_wrlock(&rwlock);
    int result = SerialLinkedList::Insert(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}

int RwLockParallelLinkedList::Remove(int data)
{
    pthread_rwlock_wrlock(&rwlock);
    int result = SerialLinkedList::Remove(data);
    pthread_rwlock_unlock(&rwlock);
    return result;
}
