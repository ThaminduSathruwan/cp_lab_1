#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
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

    void Populate(int n);

    virtual bool Member(int data) = 0;
    virtual bool Insert(int data) = 0;
    virtual bool Remove(int data) = 0;

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
    virtual ~SerialLinkedList() {}

    virtual bool Member(int data) override;
    virtual bool Insert(int data) override;
    virtual bool Remove(int data) override;
};

class MutexParallelLinkedList : public SerialLinkedList
{
public:
    MutexParallelLinkedList() : SerialLinkedList()
    {
        pthread_mutex_init(&mutex, NULL);
    }

    ~MutexParallelLinkedList()
    {
        pthread_mutex_destroy(&mutex);
    }

    bool Member(int data) override;
    bool Insert(int data) override;
    bool Remove(int data) override;

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

    ~RwLockParallelLinkedList()
    {
        pthread_rwlock_destroy(&rwlock);
    }

    bool Member(int data) override;
    bool Insert(int data) override;
    bool Remove(int data) override;

private:
    pthread_rwlock_t rwlock;
};

#endif // LINKED_LIST_H
