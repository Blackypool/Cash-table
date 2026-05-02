#ifndef DUMP_Y_FOR_ALL
#define DUMP_Y_FOR_ALL

#include "../M_Hash_tabl.h"

int dump_in_exel(struct M_Hash* all_spiski, const char* need_name, int size_of_table);

int html_diagrams(struct M_Hash* all_spiski, size_t koeff_, const char* need_name, size_t pik_of_dia, float scale___);

int global_dump_func(struct M_Hash* all_spiski);

int do_gnu_png(char* where_data, const char* need_name, int size_of_table);

int type_of_func_find(const char* type_of_f, struct M_Hash* all_spiski);


#endif