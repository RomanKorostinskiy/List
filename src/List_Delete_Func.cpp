#include <../include/List.h>

int ListDeleteBack(List* list)
{
    LIST_CHECK(__FUNCTION__);

    list->elem[list->tail].data = 0; //1

    //First element
    if(list->head == list->tail)
    {
        list->elem[list->tail].next = list->free;
        list->elem[list->tail].prev = -1;

        list->free = list->tail;
    }
        //Other element
    else
    {
        list->elem[list->tail].next = list->free; //2

        list->elem[list->elem[list->tail].prev].next = 0; //3

        list->free = list->tail; //4

        list->tail = list->elem[list->tail].prev; //5

        list->elem[list->free].prev = -1; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return list->tail;
}

int ListDeleteFront(List* list)
{
    LIST_CHECK(__FUNCTION__);

    list->elem[list->head].data = 0; //1

    int old_free = list->free;

    //First element
    if(list->head == list->tail) //(list->head == list->tail)
    {
        list->elem[list->head].next = list->free;
        list->elem[list->head].prev = -1;

        list->free = list->head;
    }
        //Other element
    else
    {
        list->elem[list->head].prev = -1; //2

        list->elem[list->elem[list->head].next].prev = 0; //3

        list->free = list->head; //4

        list->head = list->elem[list->head].next; //5

        list->elem[list->free].next = old_free; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return list->head;
}

int ListDelete(List* list, int position)
{
    LIST_CHECK(__FUNCTION__);

    if(list->elem[position].prev == -1)
    {
        printf("In Function %s: can't delete free node\n", __FUNCTION__);
        return DELETE_ERROR;
    }

    list->elem[position].data = 0; //1

    int current_elem_position = list->elem[position].prev;

    //DeleteFront/DeleteBack
    if (list->elem[position].next == 0)
        return ListDeleteBack(list);
    else if (list->elem[position].prev == 0)
        return ListDeleteFront(list);
        //Inside the list
    else
    {
        list->elem[list->elem[position].prev].next = list->elem[position].next; //2
        list->elem[list->elem[position].next].prev = list->elem[position].prev; //3

        list->elem[position].next = list->free; //4
        list->elem[position].prev = -1; //5

        list->free = position; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return current_elem_position;
}