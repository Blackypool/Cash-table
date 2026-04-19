#ifndef HASH_TYPE_H
#define HASH_TYPE_H

#include "../M_Hash_tabl.h"

size_t hash_func(val_t wo_rd);

int find_er_w(struct List_t* spisok, val_t crusual);

int KESH_buf(struct List_t** h_ash_table, val_t crusual);

int find_u_psw(struct List_t** h_ash_table, val_t crusual);

size_t _ret_zero_hash_func(val_t wo_rd);

size_t _len_hash_func(val_t wo_rd);

size_t _first_ASCII_hash_func(val_t wo_rd);

size_t _summ_ASCII_hash_func(val_t wo_rd);

size_t _SRC_32_hash_func(val_t wo_rd);

size_t _GNU_hash_func(val_t wo_rd);


#endif