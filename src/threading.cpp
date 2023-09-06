#include <iostream>
#include <unordered_set>
#include <pthread.h>
#include "linked_list.h"
#include "threading.h"

void *thread_func(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;

    int mMember = (int)(args->mMember * args->m);
    int mInsert = (int)(args->mInsert * args->m);
    int mDelete = (int)(args->mDelete * args->m);

    // TODO: Implement this function

    return NULL;
}

void run_threads(int threadCnt, LinkedList *list,
                 std::unordered_set<int> &insertVals, std::unordered_set<int> &deleteVals,
                 int m, double mMember, double mInsert, double mDelete)
{
    // TODO: Implement this function dividing m operations into threadCnt threads
}
