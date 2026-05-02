#ifndef HASH_TYPE_H
#define HASH_TYPE_H

#include "../M_Hash_tabl.h"


int find_er_w(struct List_t* spisok, val_t crusual, size_t hash, struct M_Hash* all_spiski);

int KESH_buf(struct List_t** h_ash_table, val_t crusual, struct M_Hash* all_spiski);


typ_of_hash _ret_zero_hash_func(val_t wo_rd);

typ_of_hash _len_hash_func(val_t wo_rd);

typ_of_hash _first_ASCII_hash_func(val_t wo_rd);

typ_of_hash _summ_ASCII_hash_func(val_t wo_rd);

typ_of_hash CRC_32_hash(val_t wo_rd);

typ_of_hash _GNU_hash_func(val_t wo_rd);

typ_of_hash RO_tate_Left_hash(val_t wo_rd);

typ_of_hash RO_tate_Right_hash(val_t wo_rd);


#endif