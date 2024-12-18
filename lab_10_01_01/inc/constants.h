#ifndef CONSTANTS_H__
#define CONSTANTS_H__

// Определение кодов для цветного принта
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

// Возможные значения параметра "Операция"
/*
F - поиск
P - Вставка в начало списка
C - Копирование списка
S - Сортировка
Ошибка при выборе операции
*/
typedef enum
{
    OP_FIND,
    OP_POP_FRONT,
    OP_COPY,
    OP_SORT,
    OP_TASK,
    OP_UNKNOWN
} operations_t;

// Если флаг дебаг активен, то будут работать отдладочные принты
// 2 - Полный дебаг, 1 - Для сдачи ЛР
#define DEBUG 2
// Значение переменной argc
#define REQUIREMENT_ARG_COUNT 4

// Максимальное количество элементов в списке
// #define MAX_LIST_COUNT 5

// Максимальная длина названия
#define MAX_NAME_LEN 50

#endif
