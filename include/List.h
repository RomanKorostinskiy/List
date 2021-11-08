#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INT_DATA

#ifdef INT_DATA
typedef int data_t;
#endif
#ifdef FLOAT_DATA
typedef double data_t;
#endif

enum ListErrors
{
    DATA_NULL_PTR = 1,
    NEXT_NULL_PTR = 2,
};

//typedef struct ListElem
//{
//    data_t data = 0;
//    int next    = 0;
//    int prev    = 0;
//}ListElem;

typedef struct List
{
//    ListElem* elem = nullptr;
    data_t* data = nullptr;
    int*    next = nullptr;
    int*    prev = nullptr;

    int capacity = 0;

    int head = 0;
    int tail = 0;
}List;

const int LIST_CAPACITY = 1024;

int ListCtor(List* list, int capacity);

int ListDtor(List* list);

int ListInsertBack (List* list, int value);