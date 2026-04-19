#ifndef CONSTR_DISTR_H
#define CONSTR_DISTR_H

#include "../M_Hash_tabl.h"

int constr_HASH_table(struct M_Hash* all_spiski, size_t size_of_table);

int fill_base_of_d(struct M_Hash* all_spiski);

void cleaner_HASH_table(struct M_Hash* all_spiski);

int html_diagrams(struct M_Hash* all_spiski, size_t koeff_, const char* need_name, size_t pik_of_dia, float scale___);


#endif