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
        list->elem[i].next = i + 1;
        list->elem[i].prev = -1;
    }

    list->elem[list->capacity].next = 0;
    list->elem[0].prev              = -1;

    return 0;
}

int SetListMemPoison(List* list)
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
        printf("In function LestResize: can't realloc memory\n");
        return REALLOC_ERROR;
    }

    list->free = old_capacity + 1;

    SetListMemResize(list, old_capacity);

#ifdef LIST_DUMP
    ListDump(list, __FUNCTION__);
#endif

    return 0;
}

int GetPhysAddress(List* list, int logical_adr)
{
    int phys_adr = list->head;

    for(int i = 1; i < logical_adr; i++)
    {
        phys_adr = list->elem[phys_adr].next;

        if(phys_adr == 0)
            return -1;
    }

    return phys_adr;
}

int GetLogicalAddress(List* list, int phys_adr)
{
    if(list->elem[phys_adr].prev == -1)
        return -1;

    int logical_adr = 1;

    while(phys_adr != list->head)
    {
        logical_adr++;
        phys_adr = list->elem[phys_adr].prev;

        if(logical_adr > list->capacity)
            return -1;
    }

    return logical_adr;
}

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
        printf("In Function ListInsertBefore: can't insert before free node\n");
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
        printf("In Function ListInsertAfter: can't insert after free node\n");
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

int ListDeleteBack(List* list)
{
    LIST_CHECK(__FUNCTION__);

    if (list->head == list->free)
    {
        printf("In Function ListDeleteBack: list is empty\n");
        return INSERT_ERROR;
    }

    list->elem[list->tail].data = 0; //1

    //First element
    if(list->elem[list->tail].prev == 0)
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