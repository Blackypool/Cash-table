#include "read_bd.h"


size_t number_of_file(const char* name_file)
{
    struct stat file_info = {};

    if(stat(name_file, &file_info) != 0)
    {
        perror("stat error");
        return 1;
    }

    return (size_t)file_info.st_size;
}


char** update_bd(size_t *now_word)
{
    size_t number_char = number_of_file(file_name);

    int fd = open(file_name, O_RDWR);   // file descriptor
    AsserT(fd == -1, file_errorr, NULL);

    // желаемый адрес в памяти, количество байт, чтение/запись, изменения идут/не пишутся в файл, , оффсет
    char* ptr_to_base = (char*)mmap(NULL, number_char, PROT_READ, MAP_PRIVATE, fd, 0);
    AsserT(ptr_to_base == MAP_FAILED, file_errorr, NULL);


    size_t how_much_words = number_char / MIDDLE_of_len;
    char** full_data = (char**)calloc(how_much_words, sizeof(char*));
    AsserT(full_data == NULL, memory_aloca, NULL);

    size_t pointer_start = 0;
    for(size_t i = 0; i < number_char; i++)
    {
        if(ptr_to_base[i] == ' ' || ptr_to_base[i] == '\t' || ptr_to_base[i] == '\n' || ptr_to_base[i] == '"' || ptr_to_base[i] == '*' \
            || ptr_to_base[i] == '(' )
        {
            full_data[*now_word] = strndup(&ptr_to_base[pointer_start], i - pointer_start);
            pointer_start = i + 1;
            (*now_word)++;
        }

        else if(ptr_to_base[i] == ',' || ptr_to_base[i] == '.' || ptr_to_base[i] == '?' || ptr_to_base[i] == '!' || ptr_to_base[i] == ')')
            {    
                full_data[*now_word] =  strndup(&ptr_to_base[pointer_start], i - pointer_start);
                i++;
                pointer_start = i + 1;
                (*now_word)++;
            }
    }

    munmap(ptr_to_base, number_char);
    close(fd);

    return full_data;
}
