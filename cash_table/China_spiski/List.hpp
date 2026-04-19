#ifndef LIST_HPP
#define LIST_HPP

typedef const char* val_t;

#include "../M_Hash_tabl.h"

#include "constr_distr.hpp"
#include "dump_ing.hpp"
#include "ht_ml.hpp"


struct Node_t
{
    struct Node_t *prev;

    val_t value;
    size_t what_do_u_need;

    struct Node_t *next;
};


struct List_t
{
    size_t size = 0;

    struct Node_t *head;
    struct Node_t *tail;
};


#endif