#include "hash_types.h"

// need align with last zeroes for no trash in intrinsik crc for more byte = CRC32 for 64
// delete global struct and do last hash in main struct
// rename #define # and add hash size in this

int KESH_buf(struct List_t** h_ash_table, val_t crusual, struct M_Hash* all_spiski)
{
    AsserT(h_ash_table == NULL, give_null_ptr, -1);

    size_t hash = all_spiski->hash_func_use(crusual);

    #ifdef USE_KESH_L1
        if(hash == all_spiski->last_hash)
            if(!M_strcmp_(all_spiski->last_word, crusual))
                return (int)all_spiski->last_what_do_u_need;
    #endif

    size_t indx = hash % HASH_SIZE;

    int ret = find_er_w(h_ash_table[indx], crusual, hash, all_spiski);
    AsserT(ret < 0, error_in_deep, -1);

    return ret;
}


int find_er_w(struct List_t* spisok, val_t crusual, size_t hash, struct M_Hash* all_spiski)
{
    AsserT(spisok == NULL, give_null_ptr, -1);

    struct Node_t* node_next = spisok->head;
    for(size_t i = 0; i < spisok->size ; i++)
    {
        #ifdef PREFETCH_USE
            _mm_prefetch(node_next->next, _MM_HINT_T0);
        #endif

        if(hash == node_next->hash_of_w) [[unlikely]]
        {
            #ifdef KESH_OPT_FOR_USER
                if(!M_strcmp_(node_next->value, crusual)) [[likely]]
                {
                    #ifdef USE_KESH_L1
                        all_spiski->last_hash = hash;
                        all_spiski->last_word = crusual;
                        all_spiski->last_what_do_u_need = node_next->what_do_u_need;
                    #endif

                    #ifdef USE_KESH_L2
                        mov_to_head(spisok, node_next);
                    #endif

                    return (int)node_next->what_do_u_need;
                }
            #endif

            #ifdef MY_STRCMP_OPT
                if(!M_strcmp_(node_next->value, crusual)) [[likely]]
                    return (int)node_next->what_do_u_need;             
            #endif

            #ifdef SLOOOW_STRCMP
                if(strcmp(node_next->value, crusual) == 0)
                    return (int)node_next->what_do_u_need;
            #endif
        }

        node_next = node_next->next;

        #ifdef PREFETCH_USE
            _mm_prefetch(node_next->next, _MM_HINT_T0);
        #endif

        if(hash == node_next->hash_of_w) [[unlikely]]
        {
            #ifdef KESH_OPT_FOR_USER
                if(!M_strcmp_(node_next->value, crusual)) [[likely]]
                {
                    #ifdef USE_KESH_L1
                        all_spiski->last_hash = hash;
                        all_spiski->last_word = crusual;
                        all_spiski->last_what_do_u_need = node_next->what_do_u_need;
                    #endif

                    #ifdef USE_KESH_L2
                        mov_to_head(spisok, node_next);
                    #endif

                    return (int)node_next->what_do_u_need;
                }
            #endif

            #ifdef MY_STRCMP_OPT
                if(!M_strcmp_(node_next->value, crusual)) [[likely]]
                    return (int)node_next->what_do_u_need;             
            #endif

            #ifdef SLOOOW_STRCMP
                if(strcmp(node_next->value, crusual) == 0)
                    return (int)node_next->what_do_u_need;
            #endif
        }

        node_next = node_next->next;
    }
    fprintf(stderr, "not found [%s] = [%s]\n", crusual, node_next->value);

    return -1;
}


#ifdef SLOW_CRC32_NO_OPT
typ_of_hash CRC_32_hash(val_t wo_rd)       // _CRC_32_hash_func
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
    
    return ~crc;
}
#endif


#ifdef INTRINSIK_CRC_32
typ_of_hash CRC_32_hash(val_t wo_rd)   // in__line
{
    unsigned int CRC = 0;

    for(size_t i = 0; wo_rd[i] != '\0'; i++)
        CRC = _mm_crc32_u8(CRC, wo_rd[i]);

    return CRC;
}
#endif


#ifdef ASM_IN_CRC_32
typ_of_hash CRC_32_hash(val_t wo_rd)
{
    typ_of_hash h_h = 0;

    // __asm__ volatile(
    //         ".intel_syntax noprefix\n"

    //         "movzx   ecx, byte ptr [rdi]\n"
    //         "xor     eax, eax\n"
    //         "test    cl, cl\n"
    //         "je      return\n"
    //         "inc     rdi\n"
    // "cycle_crc32:\n"
    //         "crc32   eax, cl\n"
    //         "movzx   ecx, byte ptr [rdi]\n"
    //         "inc     rdi\n"
    //         "test    cl, cl\n"
    //         "jne     cycle_crc32\n"
    // "return:\n"

    //         ".att_syntax prefix\n"
    //                 :"=a"(h_h), "+D"(wo_rd)
    //                 ://"+D"(wo_rd)
    //                 :"memory", "rcx"
    //             );

    uint64_t *data = (uint64_t*)wo_rd;
    
    h_h = _mm_crc32_u64(h_h, data[0]);
    h_h = _mm_crc32_u64(h_h, data[1]);
    h_h = _mm_crc32_u64(h_h, data[2]);
    h_h = _mm_crc32_u64(h_h, data[3]);

    return h_h;
}
#endif


// hash_func
typ_of_hash _ret_zero_hash_func(val_t wo_rd)    
{
    DE_BUG;
    return 0;
}


typ_of_hash _len_hash_func(val_t wo_rd)       
{
    DE_BUG;
    return strlen(wo_rd);
}


typ_of_hash _first_ASCII_hash_func(val_t wo_rd) 
{
    DE_BUG;
    return (typ_of_hash)*wo_rd;
}


typ_of_hash _summ_ASCII_hash_func(val_t wo_rd)   
{
    DE_BUG;
    typ_of_hash len = strlen(wo_rd);

    typ_of_hash sum = 0;
    for(typ_of_hash i = 0; i < len; i++)
        sum = sum + (typ_of_hash)wo_rd[i];

    return sum;
}


typ_of_hash _GNU_hash_func(val_t wo_rd)        
{
    DE_BUG;
    size_t h = 5381;

    for(unsigned char c = (unsigned char)*wo_rd; c != '\0'; c = (unsigned char)*(wo_rd++))
        h = h * 33 + c;
    
    return h;
}


unsigned char ro_l(unsigned char wo_rd, int shr);
unsigned char ro_r(unsigned char wo_rd, int shr);


typ_of_hash RO_tate_Left_hash(val_t wo_rd)
{
    typ_of_hash h_h = (typ_of_hash)wo_rd[0];

    h_h = ro_l(h_h, 4);

    if(strlen(wo_rd) < 2)
        return h_h;

    h_h = h_h ^ (typ_of_hash)wo_rd[1];

    return h_h;
}

unsigned char ro_l(unsigned char wo_rd, int shr)
{
    return (wo_rd << shr) | (wo_rd >> (8 - shr));
}


typ_of_hash RO_tate_Right_hash(val_t wo_rd)
{
    typ_of_hash h_h = (typ_of_hash)wo_rd[0];

    h_h = ro_r(h_h, 4);

    if(strlen(wo_rd) < 2)
        return h_h;

    h_h = h_h ^ (typ_of_hash)wo_rd[1];

    return h_h;
}

unsigned char ro_r(unsigned char wo_rd, int shr)
{
    return (wo_rd >> shr) | (wo_rd << (8 - shr));
}
