#include <../include/List.h>

int ListInsertBackTest(List* list, int elems_num)
{
    LIST_CHECK(func);

    for (int i = 1; i <= elems_num; i++)
        ListInsertBack(list, i*10);

    return 0;
}

int ListInsertFrontTest(List* list, int elems_num)
{
    LIST_CHECK(func);

    for (int i = 1; i <= elems_num; i++)
        ListInsertFront(list, 10 - i);

    return 0;
}

int PrintListElems(List* list)
{
    LIST_CHECK(func);

    int adr = list->head;
    int i = 1;

    printf("\nPrint list\n");

    while (true)
    {
        if(list->elem[adr].next == 0)
        {
            printf("%d: %d\n", i, ListGetData(list, adr));
            break;
        }

        printf("%d: %d\n", i, ListGetData(list, adr));
        adr = list->elem[adr].next;
        i++;
    }

    return 0;
}