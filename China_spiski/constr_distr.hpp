#ifndef CONSTRUCTOR_DISTR_HPP
#define CONSTRUCTOR_DISTR_HPP

#include "List.hpp"


void constructor_sp(struct List_t *spisok);

void distruct_last_list(struct List_t *spisok);

void mov_to_head(struct List_t *spisok, struct Node_t *movable);

void first_el(struct List_t *spisok, val_t value);

void add_in_tail(struct List_t *spisok, val_t value);

void add_in_head(struct List_t *spisok, val_t value);

struct Node_t* create_node(struct List_t *spisok, val_t value);


#endif