#include <../include/List.h>

int ListCtor(List* list, int capacity)
{
    list->capacity = capacity;

    list->data = (data_t*)calloc(list->capacity, sizeof(data_t));
    list->next = (int*)   calloc(list->capacity, sizeof(int));

    memset(list->next + 1, -1, list->capacity * sizeof(int));

    list->head = 1;
    list->tail = 1;

    return 0;
}

int ListDtor(List* list)
{
    if (!list->data)
    {
        printf("In Function ListDtor: data is nullptr");
        return DATA_NULL_PTR;
    }
    if (!list->next)
    {
        printf("In Function ListDtor: neat is nullptr");
        return NEXT_NULL_PTR;
    }

    memset(list->data, (int)0XBEDABEDA, list->capacity * sizeof(data_t));
    memset(list->next, (int)0XBEDABEDA, list->capacity * sizeof(int));

    list->head = -1;
    list->tail = -1;

    return 0;
}

int ListInsertBack (List* list, int value)
{
    list->data[list->tail] = value;

    list->tail = 1;
    while (list->next[list->tail] != -1)
        list->tail++;

    list->next[list->head] = list->tail;
    list->next[list->tail] = 0;

    return list->tail;
}