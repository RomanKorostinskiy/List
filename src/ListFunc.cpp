#include <../include/List.h>

int ListCtor(List* list, int capacity)
{
    LIST_CHECK(__FUNCTION__); //TODO: использовать здесь __FUNCTION__

    list->capacity = capacity;

    list->elem = (ListElem*) calloc(list->capacity, sizeof(ListElem));

    SetListMem(list);

    list->head = 1;
    list->tail = 1;
    list->free = 1;

    ListDump(list, __FUNCTION__);

    return 0;
}

int ListDtor(List* list)
{
    LIST_CHECK(__FUNCTION__);

    SetListPoison(list);

    list->head = -1;
    list->tail = -1;
    list->free = -1;

    free(list->elem);

    return 0;
}

int SetListMem(List* list)
{
    LIST_CHECK(__FUNCTION__);

    for(int i = 1; i < list->capacity; i++)
    {
        list->elem[i].next = i + 1;

        list->elem[i].prev = -1;
    }

    return 0;
}

int SetListPoison (List* list)
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

int ListInsertBack (List* list, data_t value)
{
    LIST_CHECK(__FUNCTION__);

    list->elem[list->free].data = value; //1

    if (list->head == list->free)
    {
        list->free = list->elem[list->tail].next;

        list->elem[list->tail].next = 0;
        list->elem[list->tail].prev = 0;
    }
    else
    {
        list->elem[list->tail].next = list->free; //2
        list->elem[list->free].prev = list->tail; //3

        list->tail = list->free; //4

        list->free = list->elem[list->tail].next; //5

        list->elem[list->tail].next = 0; //6
    }

    ListDump(list, __FUNCTION__);

    return list->tail;
}

int ListCheck(List* list, const char* func)
{
    if (strcmp(func, "ListCtor") == 0)
    {
        if (list->elem != nullptr)
        {
            printf("In Function %s: List constructed twice\n", func);
            return LIST_DOUBLE_CTED;
        }
    }
    else
    {
        if (!list)
        {
            printf("In Function %s: data is nullptr\n", func);
            return LIST_NULL_PTR;
        }
        if (!list->elem)
        {
            printf("In Function %s: elem is nullptr\n", func);
            return ELEM_NULL_PTR;
        }
        if(strcmp(func, "ListInsertBack") == 0)
        {
            if (list->free > list->capacity - 1)
            {
                printf("In Function %s: list is overflowed\n", func);
                return LIST_IS_OVERFL;
            }
        }
    }

    return 0;
}

int ListDump (List* list, const char* current_function)
{
    LIST_CHECK(__FUNCTION__);

//    FILE* dump_fp = nullptr;
//
    static int dump_cnt = 0;
//
//    char* dump_file_name =  DumpFileName(dump_cnt);
//
//    dump_fp = fopen(dump_file_name, "w");
//
//    if (dump_fp == nullptr)
//    {
//        printf("In function ListDump: can't open file\n");
//        return CANT_OPEN_FILE;
//    }

//    MakeTextDump(list, dump_fp, current_function);
    MakeGraphDumpTxt(list, current_function, dump_cnt);
    MakePngFromTxt(dump_cnt);

    dump_cnt++;
//    free(dump_file_name);
//    fclose(dump_fp);

    return 0;
}

int MakeTextDump(List* list, FILE* dump_fp, const char* current_function)
{
    fprintf(dump_fp, "After function: %s\n", current_function);

    fprintf(dump_fp, "data:\t");
    for(int i = 0; i < list->capacity; i++)
        fprintf(dump_fp, "%d ", list->elem[i].data);
    fprintf(dump_fp, "\n");

    fprintf(dump_fp, "next:\t");
    for(int i = 0; i < list->capacity; i++)
        fprintf(dump_fp, "%d ", list->elem[i].next);
    fprintf(dump_fp, "\n");

    fprintf(dump_fp, "prev:\t");
    for(int i = 0; i < list->capacity; i++)
        fprintf(dump_fp, "%d ", list->elem[i].prev);
    fprintf(dump_fp, "\nhead: %d; tail: %d; free: %d", list->head, list->tail, list->free);
    fprintf(dump_fp, "\n-----------------------------\n");

    return 0;
}

int MakeGraphDumpTxt(List* list, const char* current_function, int dump_cnt)
{
    FILE* dump_fp = nullptr;

    char* dump_filename =  DumpFileName(dump_cnt, "txt");

    dump_fp = fopen(dump_filename, "w");

    if (dump_fp == nullptr)
    {
        printf("In function ListDump: can't open file\n");
        return CANT_OPEN_FILE;
    }

    fprintf(dump_fp, "digraph Dump\n"
                     "{\n"
                     "\trankdir = LR;\n");

    fprintf(dump_fp, "\t\"After function: %s\"\n\n", current_function);

    fprintf(dump_fp, "\tPointers [shape = record, label = "
                     "\" head: %d | tail: %d | free: %d \"];\n\n",
                     list->head, list->tail, list->free);

    for(int i = 0; i < list->capacity; i++)
    {
        fprintf(dump_fp, "\tNode%d [shape = record, label = "
                         "\" %d | data: %d | <next> next: %d | <prev> prev: %d\"];\n",
                         i, i, list->elem[i].data, list->elem[i].next, list->elem[i].prev);
    }

    fprintf(dump_fp, "\n\tedge[color=white]\n");

    fprintf(dump_fp, "\t");
    for(int i = 0; i < list->capacity; i++)
    {
        if(i == list->capacity - 1)
            fprintf(dump_fp, "Node%d", i);
        else
            fprintf(dump_fp, "Node%d -> ", i);
    }

    fprintf(dump_fp, "\n}");

    free(dump_filename);
    fclose(dump_fp);

    return 0;
}

int MakePngFromTxt(int dump_cnt)
{
    char* txt_to_png = nullptr;
    txt_to_png = (char*) calloc(200, sizeof(char));

    char* txt_dump_filename =  DumpFileName(dump_cnt, "txt");

    char* png_dump_filename =  DumpFileName(dump_cnt, "png");

    sprintf(txt_to_png, "cd ../ListDump/ && dot %s -T png -o %s", txt_dump_filename, png_dump_filename);

    system(txt_to_png);

    free(txt_to_png);
    free(txt_dump_filename);
    free(png_dump_filename);

    return 0;
}

char* DumpFileName(int dump_cnt, const char* format)
{
    char* dump_file_name = nullptr;

    dump_file_name = (char*) calloc(50, sizeof(char));

    if(dump_file_name == nullptr)
    {
        printf("In function DumpFileName: can't dump_file_name is nullptr");
        return nullptr;
    }

    sprintf(dump_file_name, "../ListDump/ListDump%d.%s", dump_cnt, format);

    return dump_file_name;
}