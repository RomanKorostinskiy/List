#include <../include/List.h>

int main()
{
    List list = {};

    ListCtor(&list, LIST_CAPACITY);

    ListDtor(&list);
}