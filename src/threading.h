#ifndef THREADS_H
#define THREADS_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <pthread.h>
#include "linked_list.h"

typedef struct ThreadArgs
{
    LinkedList *list;
    std::vector<int> *insertVals;
    std::vector<int> *deleteVals;
    int m;
    double mMember;
    double mInsert;
    double mDelete;
    int threadCnt;
    pthread_t *tid;
} ThreadArgs;

void *thread_func(void *arg);
void run_threads(int threadCnt, LinkedList *list,
                 std::unordered_set<int> &insertVals, std::unordered_set<int> &deleteVals,
                 int m, double mMember, double mInsert, double mDelete);

#endif // THREADS_H
