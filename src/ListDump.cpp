#include <../include/List.h>

int ListDump (List* list, const char* current_function)
{
    LIST_CHECK(__FUNCTION__);

    static int dump_cnt = 0;

    MakeGraphDumpTxt(list, current_function, dump_cnt);

    MakePngFromTxt(dump_cnt);

    dump_cnt++;

    return dump_cnt;
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

    for(int i = 0; i <= list->capacity; i++)
    {
        fprintf(dump_fp, "\tNode%d [shape = record, label = "
                         "\" %d | data: %d | <next> next: %d | <prev> prev: %d\"];\n",
                i, i, list->elem[i].data, list->elem[i].next, list->elem[i].prev);
    }

    fprintf(dump_fp, "\n\tedge[color=white]\n");

    fprintf(dump_fp, "\t");
    for(int i = 0; i <= list->capacity; i++)
    {
        if(i == list->capacity)
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

int MakeHtmlDump(int dump_cnt)
{
    FILE* dump_fp = nullptr;

    dump_fp = fopen("Dump.html", "a");

    if (dump_fp == nullptr)
    {
        printf("In function ListDump: can't open file\n");
        return CANT_OPEN_FILE;
    }

    fprintf(dump_fp, "<pre>\n");
    fprintf(dump_fp, "dump");
    fprintf(dump_fp, "<pre>\n");

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