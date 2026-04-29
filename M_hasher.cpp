#include "M_Hash_tabl.h"


int main(int argc, char* argv[])  // hash_func
{
    AsserT(argc < 2, syntax_err, 0);

    struct M_Hash all_spiski = {0};

    int err = type_of_func_find(argv[1], &all_spiski);
    AsserT(err != 0, err, 0);

    err = constr_HASH_table(&all_spiski, HASH_SIZE);
    AsserT(err != 0, err, 0);

    for(size_t num_i = 0; num_i < 400; num_i++)
    {
        for(size_t i = 0; i < all_spiski.all_word_num; i++)
        {
            err = KESH_buf(all_spiski.h_ash_table, all_spiski.all_word__s[i], &all_spiski);
            AsserT(err < 0, error_in_deep, 0);
        }
    }

    cleaner_HASH_table(&all_spiski);

    return 0;
}
