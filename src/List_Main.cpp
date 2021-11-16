#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_START_CAPACITY);

//
    ListInsertBackTest(&list, 3);
    ListInsertFrontTest(&list, 2);

    ListInsertBefore(&list, GetPhysAddress(&list, 2), 1);
    ListInsertAfter(&list, 1, 1);

    ListDeleteBack(&list);

    ListInsertBack(&list, 15);

    ListDeleteFront(&list);

    ListDelete(&list, 2);
    ListDelete(&list, 1);
    ListDelete(&list, 3);

    ListInsertInstead(&list, 4, 228);
//    ListDelete(&list, 4);
//    ListDelete(&list, 6);
//    ListDelete(&list, 5);
//

    ListDtor(&list);
}