#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#define HASH_SIZE 307

#define file_name "poems/_Leo_Tolstoy.txt"
#define MIDDLE_of_len 4


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <cstdint>
#include <optional>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

#include "construct_H_t/read_bd.h"
#include "China_spiski/List.hpp"
#include "construct_H_t/hash_types.h"
#include "construct_H_t/do_and_crash_t.h"


struct Cash_
{
    const char* word_1;
    const char* word_2;

    size_t indx_of_1;
    size_t indx_of_2;
};
extern struct Cash_ L1_kesh;


struct M_Hash
{
    struct List_t** h_ash_table;
    
    size_t now_word;

    size_t rate_of_t;
};


enum errors_
{
    memory_aloca = 1,

    oversize_any = 2,
    
    syntax_err   = 3,

    give_null_ptr = 4,
    
    file_errorr = 5,

    error_in_deep = 6,
};

//_____________________________________________________________________________________________
#define AsserT(what_need, type_err, retern)                                                    \
            if(what_need){                                                                      \
                fprintf(stderr, "\n\nerror in line, %s:%d. Problem with:", __FILE__, __LINE__);  \
                switch(type_err)                                                                  \
                {                                                                                  \
                    case memory_aloca:                                                              \
                        fprintf(stderr, " memory allocation \n");                                    \
                    break;                                                                            \
                                                                                                       \
                    case oversize_any:                                                                  \
                        fprintf(stderr, " oversize \n");                                                 \
                    break;                                                                                \
                                                                                                           \
                    case syntax_err:                                                                        \
                        fprintf(stderr, " some syntax error \n");                                            \
                    break;                                                                                    \
                                                                                                               \
                    case give_null_ptr:                                                                         \
                        fprintf(stderr, " you give here NULL ptr \n");                                           \
                    break;                                                                                        \
                                                                                                                   \
                    case file_errorr:                                                                               \
                        fprintf(stderr, " problem with openning file \n");                                           \
                    break;                                                                                            \
                                                                                                                       \
                    case error_in_deep:                                                                                 \
                        fprintf(stderr, " error in return of upper func \n");                                            \
                    break;                                                                                                \
                                                                                                                           \
                    default:                                                                                                \
                        fprintf(stderr, " undefined error \n");                                                              \
                    break;                                                                                                    \
                }                                                                                                              \
                                                                                                                                \
                return retern;                                                                                                   \
            }                                                                                                                     
//_________________________________________________________________________________________________________________________________


#endif