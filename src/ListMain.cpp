#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_CAPACITY);

    for (int i = 1; i < 4; i++)
        ListInsertBack(&list, i*10);

    ListDtor(&list);
}