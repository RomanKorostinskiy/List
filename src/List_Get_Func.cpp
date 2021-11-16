#include <../include/List.h>

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