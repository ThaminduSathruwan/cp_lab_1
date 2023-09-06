#ifndef THREADS_H
#define THREADS_H

#include <iostream>
#include <unordered_set>
#include <pthread.h>
#include "linked_list.h"

typedef struct ThreadArgs
{
    LinkedList *list;
    std::unordered_set<int> *insertVals;
    std::unordered_set<int> *deleteVals;
    int m;
    double mMember;
    double mInsert;
    double mDelete;
} ThreadArgs;

void *thread_func(void *arg);
void run_threads(int threadCnt, LinkedList *list,
                 std::unordered_set<int> &insertVals, std::unordered_set<int> &deleteVals,
                 int m, double mMember, double mInsert, double mDelete);

#endif // THREADS_H
