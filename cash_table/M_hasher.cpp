#include "M_Hash_tabl.h"


int main()  // hash_func
{   
    struct M_Hash all_spiski = {0};

    int err = constr_HASH_table(&all_spiski, HASH_SIZE);    // сделали структуру + заполнили её базой слов
    AsserT(err != 0, err, 0);

    err = find_u_psw(all_spiski.h_ash_table, "sky");
    AsserT(err < 0, error_in_deep, 0);
    fprintf(stderr, "position of your word %s is %d\n", "sky", err + 1);

    // graph_fhiz(&all_spiski);

    html_diagrams(&all_spiski, 50, "summ of ASCII", 7800, 0.7f);

    cleaner_HASH_table(&all_spiski);

    return 0;
}
