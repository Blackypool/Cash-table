#include "dump_ing.hpp"

void ffprintff(struct List_t* spisok, const char* text, int *number_of_zapusk, ...)
{
    char str[35] = {};
    snprintf(str, sizeof str, "dumpy/dot.dot/list_dump_%d.dot", *number_of_zapusk);

    FILE *fp_out = fopen(str, "w");
    AsserT(fp_out == NULL, file_errorr, );

    fprintf(fp_out, "digraph\n{\nrankdir=LR;\nnodesep=0.4;\nranksep=1.0;\n  node [shape = \"star\", style = \"filled\", \
                fillcolor = \"#dc143c\", fontcolor = \"#ffffffff\"];\n");


    fprintf(fp_out, "  labelloc=\"t\";\n");
    fprintf(fp_out, "  label=\"");
    

    va_list ap;

    va_start(ap, number_of_zapusk);
    
    vfprintf(fp_out, text, ap);

    va_end(ap);


    if(spisok == NULL)
    {
        fprintf(fp_out, "   \ncase_0  [label = \"val = 0 |   {prev = 0 | next = 0}\", shape = \"rectangle\", style = \"rounded\", \
            style = \"filled\", fillcolor = \"#d5f33dff\", fontcolor = \"#000000\", shape = Mrecord];\n");

        (*number_of_zapusk)++;
        
        fprintf(fp_out, "\n}");

        fclose(fp_out);

        return ;
    }
    

    fprintf(fp_out, "\nHEAD: %p = [%s]\nTAIL: %p = [%s]\nSIZE: %zu\";\n", spisok->head, spisok->head->value, \
                spisok->tail, spisok->tail->value, spisok->size);


    fprintf(fp_out, "   case_%p  [label = \"val = %s |   {prev = %p | next = %p}\", shape = \"rectangle\", style = \"rounded\", \
        style = \"filled\", fillcolor = \"#7FFFD4\", fontcolor = \"#000000\", shape = Mrecord];\n", spisok->head, spisok->head->value,\
            spisok->head->prev, spisok->head->next);


    struct Node_t *fict = spisok->head->next;
    //заполняем ячейки
    while(fict != spisok->head)
    { 
                                        //7FFFD4    7FFFD4
        fprintf(fp_out, "   case_%p  [label = \"val = %s |   {prev = %p | next = %p}\", shape = \"rectangle\", style = \"rounded\", \
            style = \"filled\", fillcolor = \"#7FFFD4\", fontcolor = \"#000000\", shape = Mrecord];\n", fict, fict->value,\
                fict->prev, fict->next);

        fict = fict->next;
    }

    //выравниваем    
    fprintf(fp_out, "\n\n   {edge[style = \"invis\", weight = 100000];\n");

    fict = spisok->head->next;
    while(fict != spisok->head)
    {
        fprintf(fp_out, "   case_%p->case_%p;\n", fict, fict->next);
        fprintf(fp_out, "   case_%p->case_%p;\n", fict->next, fict);
        fict = fict->next;
    }

    fprintf(fp_out, "   }\n");


    //HEAD/TAIL
    fprintf(fp_out, "   case_111  [label = \"HEAD\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#000080\", fontcolor = \"#ffffff\"];\n");
    fprintf(fp_out, "   case_111->case_%p[color = \"#0000FF\", weight = 10];\n", spisok->head);

    fprintf(fp_out, "   case_222  [label = \"TAIL\", shape = \"rectangle\", style = \"filled\", fillcolor = \"#000080\", fontcolor = \"#ffffff\"];\n");
    fprintf(fp_out, "   case_222->case_%p[color = \"#0000FF\", weight = 10];\n", spisok->tail);


    //соединяем в нужном порядке
    // fprintf(fp_out, "   case_%p->case_%p[color = \"#0000FF\", weight = 10];\n", spisok->head, spisok->head->prev);

    fict = spisok->head->next;
    while(fict != spisok->head)
    {
        fprintf(fp_out, "   case_%p->case_%p[color = \"#0000FF\", weight = 10];\n", fict, fict->next);
        fprintf(fp_out, "   case_%p->case_%p[color = \"#0000FF\", weight = 10];\n", fict->next, fict);
        fict = fict->next;
    }


    //энд
    fprintf(fp_out, "\n}");

    fclose(fp_out);

    call_terminal(*number_of_zapusk);

    (*number_of_zapusk)++;
}


void call_terminal(int number_of_zapusk) 
{
    char apple_script[512] = {};

    snprintf(apple_script, sizeof(apple_script), "cd dumpy/dot.dot && dot -Tpng list_dump_%d.dot -o ../dot.png/phg_spisok%d.png", number_of_zapusk, number_of_zapusk);
    
    system(apple_script);
}


void graph_fhiz(struct M_Hash* all_spiski)
{
    int number_of_zapusk = 0;

    for(size_t i = 0; i < HASH_SIZE; i++)
        ffprintff(all_spiski->h_ash_table[i], "in cash posi [%d]", &number_of_zapusk, i);

    go_to_html(number_of_zapusk);
}
