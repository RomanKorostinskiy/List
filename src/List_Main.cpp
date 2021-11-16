#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_START_CAPACITY);

//по кайфу
    ListInsertBackTest(&list, 3);
    ListInsertFrontTest(&list, 2);

    ListInsertBefore(&list, GetPhysAddress(&list, 2), 145);
    ListInsertAfter(&list, 1, 337);

    ListDeleteBack(&list);

    ListInsertBack(&list, 15);

    ListDeleteFront(&list);

    ListDelete(&list, 2);
    ListDelete(&list, 1);
    ListDelete(&list, 3);

    ListInsertInstead(&list, 4, 228);

    PrintListElems(&list);

    ListSort(&list);

    ListInsertBackTest(&list, 3);
    ListInsertFrontTest(&list, 2);

    ListInsertBefore(&list, GetPhysAddress(&list, 2), 145);
    ListInsertAfter(&list, 1, 337);

    ListDeleteBack(&list);

    ListInsertBack(&list, 15);

    ListDeleteFront(&list);

    ListDelete(&list, 2);
    ListDelete(&list, 1);
    ListDelete(&list, 3);

    ListInsertInstead(&list, 4, 228);

    PrintListElems(&list);

    ListSort(&list);
//

    ListDtor(&list);
}