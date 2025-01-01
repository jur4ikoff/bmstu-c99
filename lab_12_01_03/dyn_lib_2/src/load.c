#include "load.h"
#include "dlfcn.h"
#include "errors.h"

/**
 * @brief Функция загружает функции из динамической библиотеки
 * @param handle Указатель на переменную для работы с dl. Должна быть после dlopen
 * @param[in] load Структура указателей на функцию
 * @return код возврата
 */
int load_all_funtions_from_dyn_lib(void *handle, load_lib_t *load)
{
    if (handle == NULL)
        return ERR_POINTER;

    void *cur = NULL;
    cur = dlsym(handle, "file_elements_count");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->file_elements_count = cur;

    cur = dlsym(handle, "file_write_int");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->file_write_int = cur;

    cur = dlsym(handle, "copy_array");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->copy_array = cur;

    cur = dlsym(handle, "print_array");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->print_array = cur;

    cur = dlsym(handle, "create_array_from_file");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->create_array_from_file = cur;

    cur = dlsym(handle, "mysort");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->mysort = cur;

    cur = dlsym(handle, "find_last_neg_el");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->find_last_neg_el = cur;

    cur = dlsym(handle, "key");
    if (cur == NULL)
    {
        return ERR_LOAD_LIB;
    }
    *(void **)&load->key = cur;
    return ERR_OK;
}
