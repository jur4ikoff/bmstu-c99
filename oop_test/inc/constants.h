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
    OP_OUT,
    OP_MULT,
    OP_SQRT,
    OP_DIV,
    OP_UNKNOWN
} operations_t;

// Если флаг дебаг активен, то будут работать отдладочные принты
// 2 - Полный дебаг, 1 - Для сдачи ЛР
#define DEBUG 0
// Значение переменной argc
#define OPERATION_STRING_LEN 3

// Максимальная длина названия
#define MAX_OPERATION_LEN 5
#endif
