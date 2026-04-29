#include "hash_types.h"

#ifdef KESH_OPT_FOR_USER
static struct Cash_ L1_kesh =
{
    .word_1 = "emprissionism",
    .word_2 = "kubufuturism",

    .indx_of_1 = 0,
    .indx_of_2 = 0,

    .hash_1 = 0,
    .hash_2 = 0,
};
#endif


static struct enum_into_func func_sions[] = {

    {"zero", _ret_zero_hash_func},
    {"len", _len_hash_func},
    {"first_ASCII", _first_ASCII_hash_func},
    {"sum_ASCII", _summ_ASCII_hash_func},
    {"CRC32", CRC_32_hash},
    {"GNU", _GNU_hash_func},
    {"ro_l", RO_tate_Left_hash},
    {"ro_r", RO_tate_Right_hash},
    
};


int KESH_buf(struct List_t** h_ash_table, val_t crusual, struct M_Hash* all_spiski)
{
    AsserT(h_ash_table == NULL, give_null_ptr, -1);

    size_t hash = all_spiski->hash_func_use(crusual); // hash_func(crusual);
    size_t indx = hash % HASH_SIZE;

    #ifdef KESH_OPT_FOR_USER
        if(indx == L1_kesh.hash_1)
            if(M_strcmp_(L1_kesh.word_1, crusual))
                return (int)L1_kesh.indx_of_1;
        
        if(indx == L1_kesh.hash_2)
            if(M_strcmp_(L1_kesh.word_2, crusual))
                return (int)L1_kesh.indx_of_2;
    #endif

    int ret = find_er_w(h_ash_table[indx], crusual, hash);
    AsserT(ret < 0, error_in_deep, -1);

    return ret;
}


int find_er_w(struct List_t* spisok, val_t crusual, size_t hash) // ключевой
{
    AsserT(spisok == NULL, give_null_ptr, -1);

    struct Node_t* node_next = spisok->head;
    for(size_t i = 0; i < spisok->size; i++)
    {
        #ifdef PREFETCH_USE
            _mm_prefetch(node_next->next, _MM_HINT_T0);
        #endif

        if(hash == node_next->hash_of_w) // [[unlikely]]
        {
            #ifdef MY_STRCMP_OPT
                if(!M_strcmp_(node_next->value, crusual)) //[[likely]] // optimization_s/my_strcmp.o
                    return (int)node_next->what_do_u_need;             
            #endif

            #ifdef SLOOOW_STRCMP
                if(strcmp(node_next->value, crusual) == 0)
                    return (int)node_next->what_do_u_need;
            #endif

            #ifdef KESH_OPT_FOR_USER
                if(!M_strcmp_(node_next->value, crusual))
                {
                    fprintf(stderr, "нашли %s = %s\n", crusual, node_next->value);

                    // updete КЭШ L1
                    L1_kesh.word_1 = L1_kesh.word_2;
                    L1_kesh.indx_of_1 = L1_kesh.indx_of_2;
                    L1_kesh.hash_1 = L1_kesh.hash_2;

                    L1_kesh.word_2 = crusual;
                    L1_kesh.indx_of_2 = node_next->what_do_u_need;
                    L1_kesh.hash_2 = hash;

                    // updete КЭШ L2
                    mov_to_head(spisok, node_next);

                    return (int)node_next->what_do_u_need;
                }
            #endif
        }

        node_next = node_next->next;
    }
    fprintf(stderr, "not found %s = %s\n", crusual, node_next->value);

    return -1;
}


int type_of_func_find(char* type_of_f, struct M_Hash* all_spiski)
{
    size_t num_of_hash_func = sizeof(func_sions) / sizeof(func_sions[0]);

    for(size_t i = 0; i < num_of_hash_func; i++)
        if(strcmp(type_of_f, func_sions[i].name_of_func) == 0)
        {
            all_spiski->hash_func_use = func_sions[i].hash_func_use;

            return 0;
        }

    return error_in_deep;
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

    __asm__ volatile(
            ".intel_syntax noprefix\n"

            "movzx   ecx, byte ptr [rdi]\n"
            "xor     eax, eax\n"
            "test    cl, cl\n"
            "je      return\n"
            "inc     rdi\n"
    "cycle_crc32:\n"
            "crc32   eax, cl\n"
            "movzx   ecx, byte ptr [rdi]\n"
            "inc     rdi\n"
            "test    cl, cl\n"
            "jne     cycle_crc32\n"
    "return:\n"

            ".ATT_syntax prefix\n"
                    :"=a"(h_h), "+D"(wo_rd)
                    ://"+D"(wo_rd)
                    :"memory", "rcx"
                );

    return h_h;
}
#endif


// hash_func
typ_of_hash _ret_zero_hash_func(val_t wo_rd)     // _ret_zero_hash_func
{
    DE_BUG;
    return 0;
}


typ_of_hash _len_hash_func(val_t wo_rd)          // _len_hash_func
{
    DE_BUG;
    return strlen(wo_rd);
}


typ_of_hash _first_ASCII_hash_func(val_t wo_rd)  // _first_ASCII_hash_func
{
    DE_BUG;
    return (typ_of_hash)*wo_rd;
}


typ_of_hash _summ_ASCII_hash_func(val_t wo_rd)   // _summ_ASCII_hash_func
{
    DE_BUG;
    typ_of_hash len = strlen(wo_rd);

    typ_of_hash sum = 0;
    for(typ_of_hash i = 0; i < len; i++)
        sum = sum + (typ_of_hash)wo_rd[i];

    return sum;
}


typ_of_hash _GNU_hash_func(val_t wo_rd)          // _GNU_hash_func
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
