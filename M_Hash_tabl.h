#ifndef HASH_TABLE_H
#define HASH_TABLE_H

//____________________________________________Kesh optimization_______________________________________________________________
// #define KESH_OPT_FOR_USER

// #define USE_KESH_L1
// #define USE_KESH_L2


//_________________________________________________optimization_______________________________________________________________
#define PREFETCH_USE

// #define SLOW_CRC32_NO_OPT
// #define INTRINSIK_CRC_32
#define ASM_IN_CRC_32

// #define SLOOOW_STRCMP
#define MY_STRCMP_OPT


//___________________________________________________HASH_SIZE_______________________________________________________________
#define HASH_SIZE 7937              // load factor = numslov / size
#define CAN_CHANGE_HASH_SIZE 4001
//____________________________________________________________________________________________________________________________


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

// #include <x86intrin.h>
// #include <immintrin.h>


//___________________________________________BASH_S___________________________________________________________________________

// nasm -f elf64 -l optimization_s/my_strcmp.lst optimization_s/my_strcmp.asm
// nasm -f elf64 -o optimization_s/my_strcmp.o optimization_s/my_strcmp.asm

// sudo perf record -g ./a.out CRC32
// sudo perf report

// sudo perf stat -r10 ./a.out CRC32

// hyperfine --warmup 2 --runs 10 './a.out CRC_32_hash'

//____________________________________________________________________________________________________________________________


extern "C" int M_strcmp_(const char* ptr_1, const char* ptr_2);    


#define MAX_LEN_IN_FILE 32
// typedef const char* val_t;
typedef char val_t[MAX_LEN_IN_FILE];

typedef size_t typ_of_hash;
typedef typ_of_hash (*func_t)(val_t wo_rd);


struct M_Hash
{
    func_t hash_func_use;

    struct List_t** h_ash_table;

    char** all_word__s;
    
    size_t all_word_num;

    //////////////// for_user
    size_t last_hash;

    const char*  last_word;

    size_t last_what_do_u_need;
};


struct enum_into_func
{
    const char* name_of_func;

    func_t hash_func_use;

    int table_size;
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


#define DE_BUG

#ifndef DE_BUG
#define DE_BUG fprintf(stderr, "\n\nfunc %s:%d. just check workli", __FILE__, __LINE__)
#endif


//////////////////////////////////////////
#include "construct_H_t/read_bd.h"
#include "China_spiski/List.hpp"
#include "construct_H_t/hash_types.h"
#include "construct_H_t/do_and_crash_t.h"
#include "construct_H_t/dump_s.h"
//////////////////////////////////////////


#endif