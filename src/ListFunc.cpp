#include <../include/List.h>

int ListCtor(List* list, int capacity)
{
    LIST_CHECK(__FUNCTION__);

    list->capacity = capacity;

    list->elem = (ListElem*) calloc(list->capacity + 1, sizeof(ListElem));

    SetListMem(list);

    list->head = 1;
    list->tail = 1;
    list->free = 1;

    ListDump(list, __FUNCTION__);

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

int SetListMem(List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 1; i <= list->capacity; i++)
    {
        if(i == list->capacity)
            list->elem[i].next = 0;
        else
            list->elem[i].next = i + 1;

        list->elem[i].prev = -1;
    }

    return 0;
}

int SetListMemPoison (List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 1; i < list->capacity; i++)
    {
        list->elem[i].data = (int)0xBEDABEDA;
        list->elem[i].next = (int)0xBEDABEDA;
        list->elem[i].prev = (int)0xBEDABEDA;
    }

    return 0;
}

int ListInsertBack (List* list, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    list->elem[list->free].data = value; //1

    if (list->head == list->free)
    {
        list->free = list->elem[list->tail].next;

        list->elem[list->tail].next = 0;
        list->elem[list->tail].prev = 0;
    }
    else
    {
        list->elem[list->tail].next = list->free; //2
        list->elem[list->free].prev = list->tail; //3

        list->tail = list->free; //4

        list->free = list->elem[list->tail].next; //5

        list->elem[list->tail].next = 0; //6
    }

    ListDump(list, __FUNCTION__);

    return list->tail;
}