#ifndef HASH_TABLE_H
#define HASH_TABLE_H

//////////////////////////////// optimization
// #define PREFETcH_ASM_IN
// #define KESH_OPT_FOR_USER
#define PREFETCH_USE

// #define SLOW_CRC32_NO_OPT
// #define INTRINSIK_CRC_32
#define ASM_IN_CRC_32

// #define SLOOOW_STRCMP
#define MY_STRCMP_OPT
////////////////////////////////


#define HASH_SIZE 7937            // load factor = numslov / size

// War&P stat: all = 571452  //  unic = 23819
#define file_name "poems/_Leo_Tolstoy.txt"

// Onegin stat: all = 34709  // unic = 8383
// #define file_name "poems/onegin.txt"

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

#include <x86intrin.h>
#include <immintrin.h>


// nasm -f elf64 -l optimization_s/my_strcmp.lst optimization_s/my_strcmp.asm
// nasm -f elf64 -o optimization_s/my_strcmp.o optimization_s/my_strcmp.asm

// perf record -g ./a.out
// perf stat -r10 ./a.out
// perf report

// hyperfine --warmup 2 --runs 10 ./a.out


extern "C" int M_strcmp_(const char* ptr_1, const char* ptr_2);    // 1 = совпали // 0 = не совпали


typedef const char* val_t;

typedef size_t typ_of_hash;
typedef typ_of_hash (*func_t)(val_t wo_rd);


struct M_Hash
{
    func_t hash_func_use;

    struct List_t** h_ash_table;

    char** all_word__s;
    
    size_t all_word_num;
};


struct enum_into_func
{
    const char* name_of_func;

    func_t hash_func_use;
};


struct Cash_
{
    const char* word_1;
    const char* word_2;

    size_t indx_of_1;
    size_t indx_of_2;

    size_t hash_1;
    size_t hash_2;
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

#define DE_BUG

#ifndef DE_BUG
#define DE_BUG fprintf(stderr, "\n\nfunc %s:%d. just check workli", __FILE__, __LINE__)
#endif

//_____________________________________________________________________________________________
#ifndef AsserT
#define AsserT(what_need, type_err, retern)                                                   \
            if(what_need) [[unlikely]]                                                         \
            {                                                                                   \
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


//////////////////////////////////////////
#include "construct_H_t/read_bd.h"
#include "China_spiski/List.hpp"
#include "construct_H_t/hash_types.h"
#include "construct_H_t/do_and_crash_t.h"
//////////////////////////////////////////


#endif