#include <iostream>
#include <set>
#include <pthread.h>
#include "linked_list.h"
#include "threading.h"

void *thread_func(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;

    // Member
    int mMemberLocal = (int)(args->mMember * args->m) / args->threadCnt;
    for (int i = 0; i < mMemberLocal; ++i)
    {
        int data = std::rand() % (1 << 16);
        args->list->Member(data);
    }

    // Delete
    int mDeleteLocal = (int)(args->mDelete * args->m) / args->threadCnt;
    int myFirstDeleteIndex = ((int)(*args->tid)) * mDeleteLocal;
    int myLastDeleteIndex = myFirstDeleteIndex + mDeleteLocal;
    for (int i = myFirstDeleteIndex; i < myLastDeleteIndex; ++i)
    {
        args->list->Remove((*args->deleteVals)[i]);
    }

    // Insert
    int mInsertLocal = (int)(args->mInsert * args->m) / args->threadCnt;
    int myFirstInsertIndex = ((int)(*args->tid)) * mInsertLocal;
    int myLastInsertIndex = myFirstInsertIndex + mInsertLocal;
    for (int i = myFirstInsertIndex; i < myLastInsertIndex; ++i)
    {
        args->list->Insert((*args->insertVals)[i]);
    }

    return NULL;
}

void run_threads(int threadCnt, LinkedList *list,
                 std::set<int> &insertVals, std::set<int> &deleteVals,
                 int m, double mMember, double mInsert, double mDelete)
{
    std::vector<int> insertValsVec(insertVals.begin(), insertVals.end());
    std::vector<int> deleteValsVec(deleteVals.begin(), deleteVals.end());

    pthread_t *threads = new pthread_t[threadCnt];
    ThreadArgs *args = new ThreadArgs[threadCnt];
    for (int i = 0; i < threadCnt; ++i)
    {
        args[i].list = list;
        args[i].insertVals = &insertValsVec;
        args[i].deleteVals = &deleteValsVec;
        args[i].m = m;
        args[i].mMember = mMember;
        args[i].mInsert = mInsert;
        args[i].mDelete = mDelete;
        args[i].threadCnt = threadCnt;
        args[i].tid = &threads[i];
        pthread_create(&threads[i], NULL, thread_func, args + i);
    }

    for (int i = 0; i < threadCnt; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    delete[] args;
    delete[] threads;
}
