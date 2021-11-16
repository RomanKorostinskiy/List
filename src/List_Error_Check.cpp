#include <../include/List.h>

int ListErrorCheck(List* list, const char* func)
{
    if (strcmp(func, "ListCtor") == 0)
    {
        if (list->elem != nullptr)
        {
            printf("In Function %s: List constructed twice\n", func);
            ListDump(list, __FUNCTION__);
            return LIST_DOUBLE_CTED;
        }
    }
    else
    {
        if (!list)
        {
            printf("In Function %s: data is nullptr\n", func);
            return LIST_NULL_PTR;
        }
        if (!list->elem)
        {
            printf("In Function %s: elem is nullptr\n", func);
            return ELEM_NULL_PTR;
        }

        if(strcmp(func, "ListInsertBack") == 0 || strcmp(func, "ListInsertFront") == 0 ||
           strcmp(func, "ListInsertBefore") == 0 || strcmp(func, "ListInsertAfter") == 0)
        {
            if (list->free > list->capacity)
            {
                printf("In Function %s: list is overflowed\n", func);
                ListDump(list, __FUNCTION__);
                return LIST_IS_OVERFL;
            }
            if (list->elem[list->free].prev != -1)
            {
                printf("In Function %s: an attempt to insert into a non-free node\n", func);
                ListDump(list, __FUNCTION__);
                return INSERT_ERROR;
            }
        }

        if(strcmp(func, "ListDeleteBack") == 0 || strcmp(func, "ListDeleteFront") == 0 ||
           strcmp(func, "ListGetBack") == 0 || strcmp(func, "ListGetFront") == 0 ||
           strcmp(func, "ListDelete") == 0 || strcmp(func, "ListGet") == 0)
        {
            if (list->head == list->free)
            {
                printf("In Function %s: list is empty\n", func);
                ListDump(list, __FUNCTION__);
                return DELETE_ERROR;
            }
        }

    }

    return 0;
}