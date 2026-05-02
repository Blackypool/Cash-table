#include "constr_distr.hpp"


void constructor_sp(struct List_t *spisok)
{
    AsserT(spisok == NULL, give_null_ptr, );

    spisok->head = NULL;
    spisok->tail = NULL;
    spisok->size = 0;
}


struct Node_t* create_node(struct List_t *spisok, val_t value)
{
    AsserT(spisok == NULL, give_null_ptr, NULL);

    struct Node_t* new_node = (struct Node_t*)calloc(1, sizeof(struct Node_t));
    AsserT(new_node == NULL, memory_aloca, NULL);

    memcpy(new_node->value, value, MAX_LEN_IN_FILE);
    // new_node->value = value;

    (spisok->size)++;

    return new_node;
}


void add_in_head(struct List_t *spisok, val_t value)
{
    AsserT(spisok == NULL, give_null_ptr, );

    struct Node_t *new_node = create_node(spisok, value);
    AsserT(new_node == NULL, memory_aloca, );

    new_node->next = spisok->head;
    new_node->prev = spisok->tail;

    spisok->head->prev = new_node;
    spisok->tail->next = new_node;

    spisok->head = new_node;
}


void add_in_tail(struct List_t *spisok, val_t value)
{
    AsserT(spisok == NULL, give_null_ptr, );

    struct Node_t *new_node = create_node(spisok, value);
    AsserT(new_node == NULL, memory_aloca, );

    new_node->next = spisok->head;
    new_node->prev = spisok->tail;

    spisok->head->prev = new_node;
    spisok->tail->next = new_node;

    spisok->tail = new_node;
}


void first_el(struct List_t *spisok, val_t value)
{
    AsserT(spisok == NULL, give_null_ptr, );

    struct Node_t *new_node = create_node(spisok, value);
    AsserT(new_node == NULL, memory_aloca, );

    spisok->head = new_node;
    spisok->tail = new_node;

    spisok->head->next = new_node;
    spisok->head->prev = new_node;
}


void mov_to_head(struct List_t *spisok, struct Node_t *movable)
{
    AsserT(spisok == NULL,  give_null_ptr, );
    AsserT(movable == NULL, give_null_ptr, );

    if(movable == spisok->head)
        return ;

    if(movable == spisok->tail)
        spisok->tail = movable->prev;

    // вырезаем
    movable->next->prev = movable->prev;
    movable->prev->next = movable->next;

    // апдейт сам узел
    movable->next = spisok->head;
    movable->prev = spisok->tail;

    //апдейт голову и хвост
    spisok->head->prev = movable;
    spisok->tail->next = movable;

    // апдейт мейн ифно
    spisok->head = movable;
}


void distruct_last_list(struct List_t *spisok)   //передаем указатель на голову
{
    if(spisok == NULL)
        return ;
    
    struct Node_t *fict = spisok->head;
    struct Node_t *fict_fict = NULL;

    for(size_t i = 0; i < spisok->size; ++i)
    {
        fict_fict = fict;
        fict = fict->next;

        // free((void*)fict_fict->value);
        free(fict_fict);
    }

    spisok->head = NULL;
    spisok->tail = NULL;

    spisok->size = 0;
}
