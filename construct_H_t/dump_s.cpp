#include "dump_s.h"

#define FIND_FUNC(need, size_need) {#need, need, size_need},

static struct enum_into_func func_sions[] = {

    FIND_FUNC(_ret_zero_hash_func,       HASH_SIZE)
    FIND_FUNC(_len_hash_func,            HASH_SIZE)
    FIND_FUNC(_first_ASCII_hash_func,    HASH_SIZE)
    FIND_FUNC(_summ_ASCII_hash_func,     CAN_CHANGE_HASH_SIZE)
    FIND_FUNC(CRC_32_hash,               HASH_SIZE)
    FIND_FUNC(_GNU_hash_func,            HASH_SIZE)
    FIND_FUNC(RO_tate_Left_hash,         HASH_SIZE)
    FIND_FUNC(RO_tate_Right_hash,        HASH_SIZE)
    
};

// struct M_Hash all_spiski = {0};
// int err = global_dump_func(&all_spiski);
// AsserT(err != 0, err, 0);

int type_of_func_find(const char* type_of_f, struct M_Hash* all_spiski)
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

int global_dump_func(struct M_Hash* all_spiski)
{
    AsserT(all_spiski == NULL, give_null_ptr, give_null_ptr);

    size_t num_of_hash_func = sizeof(func_sions) / sizeof(func_sions[0]);

    for(size_t i = 0; i < num_of_hash_func; i++)
    {
        ////////// re_build hash_table:
            int err = type_of_func_find(func_sions[i].name_of_func, all_spiski);
            AsserT(err != 0, err, 0);

            err = constr_HASH_table(all_spiski, func_sions[i].table_size);
            AsserT(err != 0, err, 0);
        //////////


        err = dump_in_exel(all_spiski, func_sions[i].name_of_func, func_sions[i].table_size);
        AsserT(err != 0, err, 0);


        char str[256] = {};
        snprintf(str, sizeof str, "dumpy/gnu_plot/gnu_plot_txt/hash_%s_%d.txt", func_sions[i].name_of_func, func_sions[i].table_size);

        err = do_gnu_png(str, func_sions[i].name_of_func, func_sions[i].table_size);
        AsserT(err != 0, err, 0);


        cleaner_HASH_table(all_spiski);
    }

    return 0;
}


int dump_in_exel(struct M_Hash* all_spiski, const char* need_name, int size_of_table)
{
    char str[256] = {};
    snprintf(str, sizeof str, "dumpy/gnu_plot/gnu_plot_txt/hash_%s_%d.txt", need_name, size_of_table);

    FILE *fp = fopen(str, "w");
    AsserT(fp == NULL, file_errorr, 0);

    for(size_t i = 0; i < size_of_table; i++)
    {
        if(all_spiski->h_ash_table[i] == NULL)
        {
            fprintf(fp, "%zu\t0\n", i);
            continue;
        }
        
        fprintf(fp, "%zu\t%zu\n", i, all_spiski->h_ash_table[i]->size);
    }

    fclose(fp);

    return 0;
}


int do_gnu_png(char* where_data, const char* need_name, int size_of_table) // func_sions[i].table_size
{
    AsserT(where_data == NULL, give_null_ptr, give_null_ptr);

    char str[256] = {};
    snprintf(str, sizeof str, "dumpy/gnu_plot/gnu_params/hash_%s_%d.txt", need_name, size_of_table);

    FILE *fp = fopen(str, "w");
    AsserT(fp == NULL, file_errorr, 0);

    char string[256] = {};
    snprintf(string, sizeof string, "dumpy/gnu_plot/gnu_plot_png/hash_%s_%d.png", need_name, size_of_table);


    fprintf(fp, "   \nset terminal pngcairo size 1920,1080 \
                    \nset output '%s'                      \
                                                           \
                    \nset boxwidth 0.8                     \
                    \nset style fill solid                 \
                                                           \
                    \nplot '%s' using 1:2 with boxes lc rgb \"purple\"", string, where_data);

    fclose(fp);
    
    
    char apple_script[512] = {};

    snprintf(apple_script, sizeof(apple_script), "gnuplot %s", str);

    system(apple_script);

    return 0;
}


int html_diagrams(struct M_Hash* all_spiski, size_t koeff_, const char* need_name, size_t pik_of_dia, float scale___)
{
    char str[256] = {};
    snprintf(str, sizeof str, "dumpy/html/hash_%s.html", need_name);

    FILE *fp = fopen(str, "w");
    AsserT(fp == NULL, file_errorr, 0);

    fprintf(fp, "\n            <!DOCTYPE html>          \
\n        <html>                                        \
\n        <head>                                        \
\n            <meta charset = \"UTF-8\">                \
\n                                                      \
\n            <style>                                   \
\n                                                      \
\n            .scrolling                                \
\n            {                                         \
\n                overflow-x: auto;      /* OX scroll */\
\n                overflow-y: hidden;    /* OY skip */  \
\n            }                                         \
\n                                                      \
\n            .histo_gramms                             \
\n            {                                         \
\n                display: flex;                          /* в ряд */                   \
\n                align-items: flex-end;                  /* прижать к низу */          \
\n                height: %zupx;                          /* пик */                     \
\n                gap: 3px;                              /* r между столбиками */       \
\n                                                      \
\n                width: max-content;                     /* не позволяет сжиматься */  \
\n                min-width: 100%%;                      \
\n                                                      \
\n                transform: scale(%f);                \
\n                transform-origin: 0 0;                  /* прижать к в/л углу */      \
\n            }                                         \
\n                                                      \
\n            .column                                   \
\n            {                                         \
\n                width: 60px;                            /*  <-> of stolbik */         \
\n                background: rgb(58, 219, 184);      \
\n                transition: all 0.4s ease;              /* delta t for sleem update from kursor */ \
\n                                                      \
\n                color: transparent;                     /* skip text */               \
\n                text-align: center;                   \
\n                font-weight: bold;                    \
\n            }                                         \
\n                                                      \
\n            .column:hover                             \
\n            {                                         \
\n                opacity: 0.9;                           /* прозрачность */            \
\n                                                      \
\n                transform: scaleY(1.3);                 /* do bigger */               \
\n                background: rgb(201, 64, 64);       \
\n                                                      \
\n                color: rgb(52, 181, 255);            /* color text */              \
\n                font-size: 65px;                      \
\n            }                                         \
\n                                                      \
\n            </style>", pik_of_dia, scale___);

    fprintf(fp,"\n</head> \
                \n<body> \
                \n<div class = \"scrolling\"> \
                \n<div class = \"histo_gramms\">");
        
    for(size_t i = 0; i < HASH_SIZE; i++)
    {
        if(all_spiski->h_ash_table[i] == NULL)
        {
            fprintf(fp, "\n<div class = \"column\" style = \"height: 5px\"> 0</div>\n");
            continue;
        }
        
        size_t sz_of_sp = all_spiski->h_ash_table[i]->size;
        fprintf(fp, "\n<div class = \"column\" style = \"height: %zupx\"> %zu</div>\n", sz_of_sp * koeff_, sz_of_sp);
    }
    
    fprintf(fp, "\n</div> \
                    \n</div> \
                    \n</body> \
                    \n</html>");


    fclose(fp);

    return 0;
}
