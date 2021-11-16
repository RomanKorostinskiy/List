#include <../include/List.h>

int ListInsertBack(List* list, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    if(list->free == 0)
        ListResize(list);

    list->elem[list->free].data = value; //1

    //First element
    if (list->head == list->free)
    {
        list->free = list->elem[list->tail].next;

        list->elem[list->tail].next = 0;
        list->elem[list->tail].prev = 0;
    }
        //Other element
    else
    {
        list->elem[list->tail].next = list->free; //2
        list->elem[list->free].prev = list->tail; //3

        list->tail = list->free; //4

        list->free = list->elem[list->tail].next; //5

        list->elem[list->tail].next = 0; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return list->tail;
}

int ListInsertFront(List* list, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    if(list->free == 0)
        ListResize(list);

    list->elem[list->free].data = value; //1

    //First element
    if (list->head == list->free)
    {
        list->free = list->elem[list->tail].next;

        list->elem[list->tail].next = 0;
        list->elem[list->tail].prev = 0;
    }
        //Other element
    else
    {
        list->elem[list->head].prev = list->free; //2
        list->elem[list->free].prev = 0; //3

        int new_free = list->elem[list->free].next;

        list->elem[list->free].next = list->head; //4

        list->head = list->free; //5

        list->free = new_free; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return list->head;
}

int ListInsertBefore(List* list, int position, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    if(list->elem[position].prev == -1)
    {
        printf("In Function %s: can't insert before free node\n", __FUNCTION__);
        return INSERT_ERROR;
    }

    if(list->free == 0)
        ListResize(list);

    list->elem[list->free].data = value; //1

    int current_elem_position = list->free;

    //Before fist element
    if (list->elem[position].prev == 0)
        return ListInsertFront(list, value);
        //Other element
    else
    {
        list->elem[current_elem_position].prev = list->elem[position].prev; //2

        list->free = list->elem[current_elem_position].next; //3

        list->elem[current_elem_position].next = list->elem[list->elem[position].prev].next; //4

        list->elem[list->elem[position].prev].next = current_elem_position; //5
        list->elem[position].prev       = current_elem_position; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return current_elem_position;
}

int ListInsertAfter(List* list, int position, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    if(list->elem[position].prev == -1)
    {
        printf("In Function %s: can't insert after free node\n", __FUNCTION__);
        return INSERT_ERROR;
    }

    if(list->free == 0)
        ListResize(list);

    list->elem[list->free].data = value; //1

    int current_elem_position = list->free;

    //After last element
    if (list->elem[position].next == 0)
        return ListInsertBack(list, value);
        //Other element
    else
    {
        list->elem[current_elem_position].prev = list->elem[list->elem[position].next].prev; //2

        list->free = list->elem[current_elem_position].next; //3

        list->elem[current_elem_position].next = list->elem[position].next; //4

        list->elem[list->elem[position].next].prev = current_elem_position; //5
        list->elem[position].next                  = current_elem_position; //6
    }

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return current_elem_position;
}

int ListInsertInstead(List* list, int position, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    if(list->elem[position].prev == -1)
    {
        printf("In Function %s: can't insert instead free node\n", __FUNCTION__ );
        return INSERT_ERROR;
    }

    list->elem[position].data = value; //1

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return position;
}