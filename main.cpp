#include <iostream>
#include <unordered_set>
#include <pthread.h>
#include "linked_list.h"

void *thread_func(void *arg);
void print_usage();

int main(int argc, char **argv)
{
    int n, m, type;

    if (argc != 3)
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

    list->Populate(n);

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
    std::cerr << "Usage: ./linked_list <n> <m> <type>" << std::endl
              << "\tn:\tnumber of initial elements in the linked list" << std::endl
              << "\tm:\tnumber of operations per thread" << std::endl
              << "\ttype:\t1 for serial, 2 for mutex, 3 for rwlock" << std::endl;
}
