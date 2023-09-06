#include <iostream>
#include <unordered_set>
#include <pthread.h>
#include "linked_list.h"

void *thread_func(void *arg);
void print_usage();

int main(int argc, char **argv)
{
    int n, m, type;

    if (argc != 7)
    {
        print_usage();
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    type = atoi(argv[3]);

    if (n <= 0 || m <= 0 || (type != 1 && type != 2 && type != 3))
    {
        print_usage();
        return 1;
    }

    double mMember, mInsert, mDelete;
    try
    {
        mMember = std::stod(argv[4]);
        mInsert = std::stod(argv[5]);
        mDelete = std::stod(argv[6]);
    }
    catch (std::exception &e)
    {
        print_usage();
        return 1;
    }

    if (mMember < 0 || mInsert < 0 || mDelete < 0 || (mMember + mInsert + mDelete) != 1)
    {
        print_usage();
        return 1;
    }

    LinkedList *list;
    switch (type)
    {
    case 1:
        list = new SerialLinkedList();
        break;
    case 2:
        list = new MutexParallelLinkedList();
        break;
    case 3:
        list = new RwLockParallelLinkedList();
        break;
    default:
        print_usage();
        return 1;
    }

    std::unordered_set<int> insertVals, deleteVals;

    list->Populate(n, m * mInsert, m * mDelete, insertVals, deleteVals);

    // TODO: Implement this

    return 0;
}

void *thread_func(void *arg)
{
    LinkedList *list = (LinkedList *)arg;

    // TODO: Implement this

    return NULL;
}

void print_usage()
{
    std::cerr << "Usage: ./linked_list <n> <m> <type> <m_Member> <m_Insert> <m_Delete>" << std::endl
              << "\tn:\t\tnumber of initial elements in the linked list" << std::endl
              << "\tm:\t\tnumber of operations per thread" << std::endl
              << "\ttype:\t\t1 for serial, 2 for mutex, 3 for rwlock" << std::endl
              << "\tm_Member:\tfraction of m operations that are member operations" << std::endl
              << "\tm_Insert:\tfraction of m operations that are insert operations" << std::endl
              << "\tm_Delete:\tfraction of m operations that are delete operations" << std::endl;
}
