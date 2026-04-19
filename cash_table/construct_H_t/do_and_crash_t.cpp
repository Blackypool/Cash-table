#include "do_and_crash_t.h"

int constr_HASH_table(struct M_Hash* all_spiski, size_t size_of_table)
{
    AsserT(all_spiski == NULL, give_null_ptr, give_null_ptr);

    struct List_t** h_t = (struct List_t**)calloc(size_of_table, sizeof(struct List_t*));
    AsserT(h_t == NULL, memory_aloca, memory_aloca);

    all_spiski->h_ash_table = h_t;

    all_spiski->rate_of_t = size_of_table;

    int err = fill_base_of_d(all_spiski);           // заполняем таблицу
    AsserT(err != 0, err, err);

    return 0;
}


int fill_base_of_d(struct M_Hash* all_spiski)
{
    AsserT(all_spiski == NULL, give_null_ptr, give_null_ptr);

    char **all_words = update_bd(&(all_spiski->now_word));
    AsserT(all_words == NULL, error_in_deep, error_in_deep);

    struct List_t** medium_Ht = all_spiski->h_ash_table;

    size_t now_word_s_in_f = all_spiski->now_word;
    // int number_of_zapusk = 0;       // for dump moment
    for(size_t i = 0; i < now_word_s_in_f; i++)
    {
        size_t indx = hash_func(all_words[i]);

        if(medium_Ht[indx] == NULL)
        {
            medium_Ht[indx] = (struct List_t*)calloc(1, sizeof(struct List_t));

            constructor_sp(medium_Ht[indx]);

            first_el(medium_Ht[indx], all_words[i]);

            medium_Ht[indx]->tail->what_do_u_need = i;    // пока будет просто номер слова лежать рядом с ним и он же при поиске кэшбэк

            // ffprintff(medium_Ht[indx], "добавили в хвост %s", &number_of_zapusk, medium_Ht[indx]->tail->value);
        }
        else 
        {
            int err = find_er_w(medium_Ht[indx], all_words[i]);

            if(err < 0)    // слова еще нет, но список есть     || error mb
            {
                add_in_tail(medium_Ht[indx], all_words[i]);

                medium_Ht[indx]->tail->what_do_u_need = i;    // пока будет просто номер слова лежать рядом с ним 
            }

            // ffprintff(medium_Ht[indx], "добавили в хвост %s", &number_of_zapusk, medium_Ht[indx]->tail->value);
        }
    }

    // go_to_html(number_of_zapusk);

    free(all_words);

    return 0;
}


void cleaner_HASH_table(struct M_Hash* all_spiski)
{
    for(size_t i = 0; i < HASH_SIZE; i++)
        distruct_last_list(all_spiski->h_ash_table[i]);

    free(all_spiski->h_ash_table);

    all_spiski->now_word  = 0;
    all_spiski->rate_of_t = 0;
}


int html_diagrams(struct M_Hash* all_spiski, size_t koeff_, const char* need_name, size_t pik_of_dia, float scale___)
{
    char str[50] = {};
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
\n                color: rgb(255, 255, 255);            /* color text */              \
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
