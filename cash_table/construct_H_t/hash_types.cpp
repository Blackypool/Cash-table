#include "hash_types.h"

struct Cash_ L1_kesh = 
{
    .word_1 = "emprissionism",
    .word_2 = "kubufuturism",
    .indx_of_1 = 0,
    .indx_of_2 = 0,
};

int find_u_psw(struct List_t** h_ash_table, val_t crusual)
{
    AsserT(h_ash_table == NULL, give_null_ptr, -1);

    int ret = KESH_buf(h_ash_table, crusual);
    AsserT(ret < 0, error_in_deep, -1);

    return ret;
}


int KESH_buf(struct List_t** h_ash_table, val_t crusual)
{
    if(strcmp(L1_kesh.word_1, crusual) == 0)
        return (int)L1_kesh.indx_of_1;
    
    if(strcmp(L1_kesh.word_2, crusual) == 0)
        return (int)L1_kesh.indx_of_2;

    size_t indx = hash_func(crusual);

    int ret = find_er_w(h_ash_table[indx], crusual);
    AsserT(ret < 0, error_in_deep, -1);

    return ret;
}


int find_er_w(struct List_t* spisok, val_t crusual) // ключевой
{
    AsserT(spisok == NULL, give_null_ptr, -1);

    struct Node_t* node_next = spisok->head;
    for(size_t i = 0; i < spisok->size; i++)
    {
        if(strcmp(node_next->value, crusual) == 0)
        {
            // updete КЭШ L1
            L1_kesh.word_1 = L1_kesh.word_2;
            L1_kesh.indx_of_1 = L1_kesh.indx_of_2;

            L1_kesh.word_2 = crusual;
            L1_kesh.indx_of_2 = node_next->what_do_u_need;

            // updete КЭШ L2
            mov_to_head(spisok, node_next);

            return (int)node_next->what_do_u_need;
        }
        
        node_next = node_next->next;
    }

    return -1;
}


// hash_func
// #define HASH_SIZE 2
size_t _ret_zero_hash_func(val_t wo_rd)     // _ret_zero_hash_func
{
    return 0 % HASH_SIZE;
}


// #define HASH_SIZE 23      // человеконенавистничество
size_t _len_hash_func(val_t wo_rd)          // _len_hash_func
{
    size_t indx = strlen(wo_rd);

    return indx % HASH_SIZE;
}


// #define HASH_SIZE 257
size_t _first_ASCII_hash_func(val_t wo_rd)  // _first_ASCII_hash_func
{
    return (size_t)*wo_rd % HASH_SIZE;
}


// #define HASH_SIZE 307
size_t hash_func(val_t wo_rd)   // _summ_ASCII_hash_func
{
    size_t len = strlen(wo_rd);

    size_t sum = 0;
    for(size_t i = 0; i < len; i++)
        sum = sum + (size_t)wo_rd[i];

    return sum % HASH_SIZE;
}


// #define HASH_SIZE 20011
size_t _SRC_32_hash_func(val_t wo_rd)       // _SRC_32_hash_func
{
    size_t len = strlen(wo_rd);
    size_t crc = 0xFFFFFFFF;
    
    for(size_t i = 0; i < len; i++)
    {
        crc = crc ^ ((unsigned char)(wo_rd[i]));
        
        for(int k = 0; k < 8; k++)
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
    }
    
    return ~crc % HASH_SIZE;
}


// #define HASH_SIZE 20011
size_t _GNU_hash_func(val_t wo_rd)          // _GNU_hash_func
{
    size_t h = 5381;

    for(unsigned char c = (unsigned char)*wo_rd; c != '\0'; c = (unsigned char)*(wo_rd++))
        h = h * 33 + c;
    
    return h % HASH_SIZE;
}
