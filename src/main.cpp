#include <iostream>
#include <set>
#include <pthread.h>
#include "linked_list.h"
#include "threading.h"

void print_usage();

int main(int argc, char **argv)
{
    int n, m, type, threadCnt;

    if (argc != 8)
    {
        print_usage();
        return 1;
    }

    n = atoi(argv[1]);
    m = atoi(argv[2]);
    type = atoi(argv[3]);
    threadCnt = atoi(argv[4]);

    if (n <= 0 || m <= 0 || (type != 1 && type != 2 && type != 3) || threadCnt <= 0)
    {
        print_usage();
        return 1;
    }

    double mMember, mInsert, mDelete;
    try
    {
        mMember = std::stod(argv[5]);
        mInsert = std::stod(argv[6]);
        mDelete = std::stod(argv[7]);
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

    std::set<int> insertVals, deleteVals;
    list->Populate(n, m * mInsert, m * mDelete, insertVals, deleteVals);
    run_threads(threadCnt, list, insertVals, deleteVals, m, mMember, mInsert, mDelete);
    delete list;

    return 0;
}

void print_usage()
{
    std::cerr << "Usage: ./linked_list <n> <m> <type> <m_Member> <m_Insert> <m_Delete>" << std::endl
              << "\tn:\t\tnumber of initial elements in the linked list" << std::endl
              << "\tm:\t\tnumber of operations per thread" << std::endl
              << "\ttype:\t\t1 for serial, 2 for mutex, 3 for rwlock" << std::endl
              << "\tthread_cnt:\tnumber of threads to use" << std::endl
              << "\tm_Member:\tfraction of m operations that are member operations" << std::endl
              << "\tm_Insert:\tfraction of m operations that are insert operations" << std::endl
              << "\tm_Delete:\tfraction of m operations that are delete operations" << std::endl;
}
