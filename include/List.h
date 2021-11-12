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
    ELEM_NULL_PTR = 1,
    LIST_NULL_PTR = 2,
};

typedef struct ListElem
{
    data_t data = 0;
    int next    = 0;
    int prev    = 0;
}ListElem;

typedef struct List
{
    ListElem* elem = nullptr;

    int capacity = 0;

    int head = 0;
    int tail = 0;
    int free = 0;
}List;

#define LIST_CHECK(func)  \
do  \
{   \
    if (!list)  \
    {   \
        printf("In Function " #func ": data is nullptr");   \
        return LIST_NULL_PTR;                               \
    }   \
    if (list->elem) \
    {   \
        printf("In Function " #func ": elem is nullptr");   \
        return ELEM_NULL_PTR;                               \
    }   \
}while (0) \

const int LIST_CAPACITY = 4;

int ListCtor (List* list, int capacity);

int ListDtor (List* list);

int ListInsertBack (List* list, int value);

int SetMem (List* list);

int SetPoison (List* list);