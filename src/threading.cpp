#include <iostream>
#include <chrono>
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
    for (int i = 0; i < mDeleteLocal; ++i)
    {
        int data = std::rand() % (1 << 16);
        args->list->Remove(data);
    }

    // Insert
    int mInsertLocal = (int)(args->mInsert * args->m) / args->threadCnt;
    for (int i = 0; i < mInsertLocal; ++i)
    {
        int data = std::rand() % (1 << 16);
        args->list->Insert(data);
    }

    return NULL;
}

long run_threads(int threadCnt, LinkedList *list,
                 int m, double mMember, double mInsert, double mDelete)
{
    std::chrono::high_resolution_clock::time_point start_time, end_time;
    start_time = std::chrono::high_resolution_clock::now();

    pthread_t *threads = new pthread_t[threadCnt];
    ThreadArgs *args = new ThreadArgs[threadCnt];
    for (int i = 0; i < threadCnt; ++i)
    {
        args[i].list = list;
        args[i].m = m;
        args[i].mMember = mMember;
        args[i].mInsert = mInsert;
        args[i].mDelete = mDelete;
        args[i].threadCnt = threadCnt;
        args[i].tid = i;
        pthread_create(&threads[i], NULL, thread_func, args + i);
    }

    for (int i = 0; i < threadCnt; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds::rep timeDiff = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

    delete[] args;
    delete[] threads;

    return (long)timeDiff;
}
