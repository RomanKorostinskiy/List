#include <../include/List.h>

int ListInsertBackTest (List* list, int elems_num)
{
    LIST_CHECK(func);

    for (int i = 1; i <= elems_num; i++)
        ListInsertBack(list, i*10);

    return 0;
}