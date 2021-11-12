#include <../include/List.h>

int ListCtor(List* list, int capacity)
{
    list->capacity = capacity;

    list->elem = (ListElem*) calloc(list->capacity, sizeof(ListElem));

    SetMem(list);

    list->head = 1;
    list->tail = 1;
    list->free = 1;

    return 0;
}

int ListDtor(List* list)
{
    LIST_CHECK(__FUNCTION__);

    SetPoison(list);

    list->head = -1;
    list->tail = -1;
    list->free = -1;

    return 0;
}

int ListInsertBack (List* list, data_t value)
{

    LIST_CHECK(__FUNCTION__);

    list->elem[list->free].data = value; //1

    if (list->head == list->free)
    {
        list->elem[list->tail].next = 0;
        list->elem[list->tail].prev = 0;

        list->free = list->elem[list->tail].next;
    }
    else
    {
        list->elem[list->tail].next = list->free; //2

        list->elem[list->free].prev = list->tail; //3

        list->tail = list->free; //4

        list->free = list->elem[list->tail].next; //5

        list->elem[list->tail].next = 0; //6
    }

    return list->tail;
}

//int ListDump (List* list)
//{
//    LIST_CHECK(__FUNCTION__);
//
//    //...
//}
//
//int ListCheck(List* list, char* func)
//{
//    if (!list)
//    {
//        printf("In Function %s: data is nullptr", func);
//        return LIST_NULL_PTR;
//    }
//    if (list->elem)
//    {
//        printf("In Function %s: elem is nullptr", func);
//        return ELEM_NULL_PTR;
//    }
//}

int SetMem(List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 1; i < list->capacity; i++)
    {
        if (i < list->capacity - 1)
            list->elem[i].next = i + 1;
        else
            list->elem[i].next = 0;

        list->elem[i].prev = -1;
    }

    return 0;
}

int SetPoison (List* list)
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