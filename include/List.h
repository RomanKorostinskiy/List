#pragma once

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
    ELEM_NULL_PTR    = 1,
    LIST_NULL_PTR    = 2,
    CANT_OPEN_FILE   = 3,
    LIST_DOUBLE_CTED = 4,
    LIST_IS_OVERFL   = 5,
    INSERT_ERROR     = 6,
};

typedef struct ListElem
{
    data_t data = 0;
    int next    = 0;
    int prev    = 0;
}ListElem;

typedef struct List
{
    ListElem* elem = nullptr; //TODO переименовать elem в node

    int capacity = 0;

    int head = 0;
    int tail = 0;
    int free = 0;
}List;

#define LIST_CHECK(func)  \
do  \
{   \
    const char* func_name = __FUNCTION__;  \
    int error = 0;  \
                    \
    if ((error = ListErrorCheck(list, func_name)) != 0) \
        return error;   \
}while (0) \

const int LIST_CAPACITY = 5;

//---------ListFunctions---------

int ListCtor (List* list, int capacity);

int ListDtor (List* list);

int SetListMem (List* list);

int SetListMemPoison (List* list);

int ListInsertBack (List* list, int value);

int ListErrorCheck(List* list, const char* func);

//---------ListDumpFunctions---------

int ListDump (List* list, const char* current_function);

int MakeTextDump(List* list, FILE* dump_fp, const char* current_function); //Больше не используется

int MakeGraphDumpTxt(List* list, const char* current_function, int dump_cnt);

int MakePngFromTxt(int dump_cnt);

int MakeHtmlDump(int dump_cnt); //Пока нормально не реализована

char* DumpFileName(int dump_cnt, const char* format);

//---------ListTestFunctions---------

int ListInsertBackTest (List* list, int elems_num);