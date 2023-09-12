#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <unordered_set>
#include <pthread.h>

class LinkedList
{
public:
    LinkedList() : head(nullptr), length(0) {}

    virtual ~LinkedList()
    {
        Node *curr = head;
        Node *next = nullptr;
        while (curr != nullptr)
        {
            next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void Populate(int n, int mInsert, int mDelete,
                  std::unordered_set<int> &insertVals, std::unordered_set<int> &deleteVals);

    virtual int Member(int data) = 0;
    virtual int Insert(int data) = 0;
    virtual int Remove(int data) = 0;

protected:
    typedef struct Node
    {
        int data;
        Node *next;
    } Node;

    Node *head;
    int length;
};

class SerialLinkedList : public LinkedList
{
public:
    SerialLinkedList() : LinkedList() {}
    ~SerialLinkedList() {}

    virtual int Member(int data) override;
    virtual int Insert(int data) override;
    virtual int Remove(int data) override;
};

class MutexParallelLinkedList : public SerialLinkedList
{
public:
    MutexParallelLinkedList() : SerialLinkedList()
    {
        pthread_mutex_init(&mutex, NULL);
    }

    ~MutexParallelLinkedList() {}

    int Member(int data) override;
    int Insert(int data) override;
    int Remove(int data) override;

private:
    pthread_mutex_t mutex;
};

class RwLockParallelLinkedList : public SerialLinkedList
{
public:
    RwLockParallelLinkedList() : SerialLinkedList()
    {
        pthread_rwlock_init(&rwlock, NULL);
    }

    ~RwLockParallelLinkedList() {}

    int Member(int data) override;
    int Insert(int data) override;
    int Remove(int data) override;

private:
    pthread_rwlock_t rwlock;
};

#endif // LINKED_LIST_H
