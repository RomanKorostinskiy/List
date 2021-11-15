#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_START_CAPACITY);

    ListInsertBackTest(&list, 3);
    ListInsertFrontTest(&list, 2);

    ListInsertBefore(&list, GetPhysAddress(&list, 2), 1);


    ListDtor(&list);
}