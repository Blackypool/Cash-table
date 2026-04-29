#include "do_and_crash_t.h"

int constr_HASH_table(struct M_Hash* all_spiski, size_t size_of_table)
{
    AsserT(all_spiski == NULL, give_null_ptr, give_null_ptr);

    struct List_t** h_t = (struct List_t**)calloc(size_of_table, sizeof(struct List_t*));
    AsserT(h_t == NULL, memory_aloca, memory_aloca);

    all_spiski->h_ash_table = h_t;                  // ptr to full table

    int err = fill_base_of_d(all_spiski);           // заполняем таблицу
    AsserT(err != 0, err, err);

    // // колво слов без повторов для подсчета лоад фактора
    // size_t num_ww = 0;
    // for(size_t i = 0; i < HASH_SIZE; i++)
    //     if(all_spiski->h_ash_table[i] != NULL)
    //         num_ww = all_spiski->h_ash_table[i]->size + num_ww;

    // fprintf(stderr, "%zu = exclusive\n\n", num_ww);
    // fprintf(stderr, "%zu = num of all\n\n", all_spiski->all_word_num);


    return 0;
}


int fill_base_of_d(struct M_Hash* all_spiski)
{
    AsserT(all_spiski == NULL, give_null_ptr, give_null_ptr);

    char **all_words = update_bd(&(all_spiski->all_word_num));      // заполянем текстом
    AsserT(all_words == NULL, error_in_deep, error_in_deep);
    all_spiski->all_word__s = all_words;

    struct List_t** medium_Ht = all_spiski->h_ash_table;

    size_t now_word_s_in_f = all_spiski->all_word_num;

    for(size_t i = 0; i < now_word_s_in_f; i++)
    {
        size_t indx = all_spiski->hash_func_use(all_words[i]); //  hash_func(all_words[i]);
        size_t ost_ind = indx % HASH_SIZE;

        if(medium_Ht[ost_ind] == NULL)
        {
            medium_Ht[ost_ind] = (struct List_t*)calloc(1, sizeof(struct List_t));

            constructor_sp(medium_Ht[ost_ind]);

            first_el(medium_Ht[ost_ind], all_words[i]);

            medium_Ht[ost_ind]->head->what_do_u_need = i;    // пока будет просто номер слова лежать рядом с ним и он же при поиске кэшбэк
            medium_Ht[ost_ind]->head->hash_of_w = indx;
        }
        else 
        {
            int err = be_in_spisok_before_li(medium_Ht[ost_ind], all_words[i], indx);

            if(err < 0)    // слова еще нет, но список есть     || error mb
            {
                add_in_tail(medium_Ht[ost_ind], all_words[i]);

                medium_Ht[ost_ind]->tail->what_do_u_need = i;    // пока будет просто номер слова лежать рядом с ним 
                medium_Ht[ost_ind]->tail->hash_of_w = indx;
            }
       }
    }

    return 0;
}


int be_in_spisok_before_li(struct List_t* spisok, val_t crusual, size_t hash)
{
    AsserT(spisok == NULL, give_null_ptr, -1);

    struct Node_t* node_next = spisok->head;
    for(size_t i = 0; i < spisok->size; i++)
    {
        if(hash == node_next->hash_of_w)
            if(strcmp(node_next->value, crusual) == 0)
                return (int)node_next->what_do_u_need;

        node_next = node_next->next;
    }

    return -1;
}


void cleaner_HASH_table(struct M_Hash* all_spiski)
{
    for(size_t i = 0; i < HASH_SIZE; i++)
        distruct_last_list(all_spiski->h_ash_table[i]);

    free(all_spiski->h_ash_table);
    free(all_spiski->all_word__s);

    all_spiski->all_word_num = 0;
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
