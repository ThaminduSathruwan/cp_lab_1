#include <iostream>
#include <fstream>
#include <pthread.h>
#include "linked_list.h"
#include "threading.h"

void print_usage();
bool print_time_diff(std::string filename, long timeDiff);

int main(int argc, char **argv)
{
    int n, m, type, threadCnt;

    if (argc != 9)
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

    std::string filename(argv[8]);
    list->Populate(n);
    long timeDiff = run_threads(threadCnt, list, m, mMember, mInsert, mDelete);
    delete list;

    return print_time_diff(filename, timeDiff) ? 0 : 1;
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
              << "\tm_Delete:\tfraction of m operations that are delete operations" << std::endl
              << "\tfilename:\tname of file to write results to" << std::endl;
}

bool print_time_diff(std::string filename, long timeDiff)
{
    std::ofstream file("results/" + filename, std::ios::app);
    if (file.fail())
    {
        std::cerr << "Failed to open file" << std::endl;
        return false;
    }

    file << timeDiff << std::endl;
    file.close();

    return true;
}
