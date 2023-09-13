#ifndef THREADS_H
#define THREADS_H

#include <iostream>
#include <pthread.h>
#include "linked_list.h"

typedef struct ThreadArgs
{
    LinkedList *list;
    int m;
    double mMember;
    double mInsert;
    double mDelete;
    int threadCnt;
    unsigned long tid;
} ThreadArgs;

void *thread_func(void *arg);
long run_threads(int threadCnt, LinkedList *list,
                 int m, double mMember, double mInsert, double mDelete);

#endif // THREADS_H
