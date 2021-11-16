#include <../include/List.h>

int ListCtor(List* list, int capacity)
{
    LIST_CHECK(__FUNCTION__);

    list->capacity = capacity;

    list->elem = (ListElem*) calloc(list->capacity + 1, sizeof(ListElem));

    SetListMemCtor(list);

    list->head = 1;
    list->tail = 1;
    list->free = 1;

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return 0;
}

int ListDtor(List* list)
{
    LIST_CHECK(__FUNCTION__);

    SetListMemPoison(list);

    list->head = -1;
    list->tail = -1;
    list->free = -1;

    free(list->elem);

    return 0;
}

int SetListMemCtor(List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 1; i <= list->capacity; i++)
    {
        list->elem[i].data = 0;
        list->elem[i].next = i + 1;
        list->elem[i].prev = -1;
    }

    list->elem[list->capacity].next = 0;

    list->elem[0].data = 0;
    list->elem[0].next = 0;
    list->elem[0].prev = -1;

    return 0;
}

int SetListMemPoison(List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 0; i <= list->capacity; i++)
    {
        list->elem[i].data = (int)0xBEDABEDA;
        list->elem[i].next = (int)0xBEDABEDA;
        list->elem[i].prev = (int)0xBEDABEDA;
    }

    return 0;
}

int SetListMemResize(List* list, int old_capacity)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = old_capacity + 1; i <= list->capacity; i++)
    {
        list->elem[i].data = 0;
        list->elem[i].next = i + 1;
        list->elem[i].prev = -1;
    }

    list->elem[list->capacity].next = 0;

    return 0;
}

int ListResize(List* list)
{
    LIST_CHECK(__FUNCTION__);

    int old_capacity = list->capacity;
    list->capacity *= CAPACITY_STEP;

    list->elem = (ListElem*) realloc(list->elem, (list->capacity + 1) * sizeof(ListElem));

    if (list->elem == nullptr)
    {
        printf("In function %s: can't realloc memory\n", __FUNCTION__);
        return REALLOC_ERROR;
    }

    list->free = old_capacity + 1;

    SetListMemResize(list, old_capacity);

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return 0;
}

int ListSort (List* list)
{
    LIST_CHECK(__FUNCTION__);

    List sorting_list = {};

    ListCtor(&sorting_list, list->capacity);

    int old_elem_adr = list->head;

    while(true)
    {
        if (list->elem[old_elem_adr].next == 0)
        {
            ListInsertBack(&sorting_list, list->elem[old_elem_adr].data);
            break;
        }

        ListInsertBack(&sorting_list, list->elem[old_elem_adr].data);

        old_elem_adr = list->elem[old_elem_adr].next;
    }

    ListDtor(list);

    *list = sorting_list;

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return 0;
}