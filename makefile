FLAGS = -O3 -mavx2
#-mavx2		optimization_s/my_strcmp.o	 China_spiski/ht_ml.cpp	China_spiski/dump_ing.cpp

FILE_S = China_spiski/constr_distr.cpp China_spiski/ht_ml.cpp China_spiski/dump_ing.cpp \
construct_H_t/do_and_crash_t.cpp construct_H_t/hash_types.cpp construct_H_t/read_bd.cpp \
M_hasher.cpp construct_H_t/dump_s.cpp

all:
	clang++ $(FLAGS) $(FILE_S)