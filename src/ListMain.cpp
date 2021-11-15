#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_CAPACITY);

    ListInsertBackTest (&list, 5);

    ListDtor(&list);
}