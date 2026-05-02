#ifndef CONSTR_DISTR_H
#define CONSTR_DISTR_H

#include "../M_Hash_tabl.h"

int constr_HASH_table(struct M_Hash* all_spiski, size_t size_of_table);

int be_in_spisok_before_li(struct List_t* spisok, val_t crusual, size_t hash);

int fill_base_of_d(struct M_Hash* all_spiski);

void cleaner_HASH_table(struct M_Hash* all_spiski);


#endif