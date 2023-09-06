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

    virtual void Member() = 0;
    virtual void Insert(int data) = 0;
    virtual void Remove(int data) = 0;

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

    void Member() override;
    void Insert(int data) override;
    void Remove(int data) override;
};

class MutexParallelLinkedList : public LinkedList
{
public:
    MutexParallelLinkedList() : LinkedList()
    {
        pthread_mutex_init(&mutex, NULL);
    }

    ~MutexParallelLinkedList() {}

    void Member() override;
    void Insert(int data) override;
    void Remove(int data) override;

private:
    pthread_mutex_t mutex;
};

class RwLockParallelLinkedList : public LinkedList
{
public:
    RwLockParallelLinkedList() : LinkedList()
    {
        pthread_rwlock_init(&rwlock, NULL);
    }

    ~RwLockParallelLinkedList() {}

    void Member() override;
    void Insert(int data) override;
    void Remove(int data) override;

private:
    pthread_rwlock_t rwlock;
};

#endif // LINKED_LIST_H
