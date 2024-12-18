/*
Варианты 1: 1,2 и 2: 1, 3:1
Аргументы указываются в формате ./app.exe OPERATION FILE_IN FILE_OUT
Возможные операции:
F - поиск
P - Вставка в начало списка
C - Копирование списка
S - Сортировка
Задача:
*/

#include "auto.h"
#include "constants.h"
#include "errors.h"
#include "linked_list.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция выводит сообщения об ошибке
static void print_error_message(int arg)
{
#if DEBUG
    printf("%s", RED);
    if (arg == ERR_ARGS_COUNT)
        printf("Ошибка, неверное количество аргументов\n");
    else if (arg == ERR_WRONG_OPERATION)
        printf("Ошибка при выборе операции\n");
    else if (arg == ERR_FILE)
        printf("Ошибка при открытии файла\n");
    else if (arg == ERR_MEMORY_ALLOCATION)
        printf("Ошибка при выделении памяти\n");
    else if (arg == ERR_STRING)
        printf("Ошибка при чтении строки из файла\n");
    else if (arg == ERR_NUMBER)
        printf("Ошибка при чтении числа из файла\n");
    else if (arg == ERR_STRUCT)
        printf("При записи структуры допущена ошибка\n");
    else if (arg == ERR_HEAD)
        printf("Ошибка при передачи списка\n");
    else if (arg == ERR_FIND)
        printf("Ошибка при поиске\n");
    else if (arg == ERR_POP)
        printf("Ошибка при удалении элемента\n");
    else if (arg == ERR_YEAR)
        printf("Ошибка, неверно введены год или стоимость\n");
    else if (arg == ERR_EMPTY_OUTPUT)
        printf("Пустой вывод\n");
    printf("%s", RESET);
#else
    (void)arg;
#endif
}

// Функция проверяет корректность аргумента операции и возвращает соответствующее значение из перечисления operations_t
static operations_t validate_operation_arg(char *argument)
{
    if (strlen(argument) != 1)
        return OP_UNKNOWN;

    if (strcmp(argument, "F") == 0)
        return OP_FIND;
    else if (strcmp(argument, "P") == 0)
        return OP_POP_FRONT;
    else if (strcmp(argument, "C") == 0)
        return OP_COPY;
    else if (strcmp(argument, "S") == 0)
        return OP_SORT;
    else if (strcmp(argument, "T") == 0)
        return OP_TASK;

    return OP_UNKNOWN;
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    node_t *head = NULL;

    // Проверка на количвество аргументов
    if (argc < REQUIREMENT_ARG_COUNT)
    {
        rc = ERR_ARGS_COUNT;
        goto exit;
    }

    // Валидация первого аргумента
    operations_t operation = validate_operation_arg(argv[1]);
    if (operation == OP_UNKNOWN)
    {
        rc = ERR_WRONG_OPERATION;
        goto exit;
    }

    // Открытие входного файлов
    FILE *file_stream = fopen(argv[2], "r");
    if (file_stream == NULL)
    {
        rc = ERR_FILE;
        goto exit;
    }

    // Загрузка списка из файла
    if ((rc = read_list(&head, file_stream)) != ERR_OK)
    {
        fclose(file_stream);
        goto exit;
    }
    // Закрываем файл, потому что он больше не используется
    fclose(file_stream);

    printf("Исходный список: \n");
    apply_list(head, print_auto);

    // Открытие выходного файла для записи результа
    FILE *file_output = fopen(argv[3], "w");
    if (file_output == NULL)
    {
        rc = ERR_FILE;
        goto exit;
    }

    // Выполнение операций
    if (operation == OP_FIND)
    {
        node_t *find_el = NULL;
        auto_t *need_data = NULL;

        int year;
        printf("Введите год выпуска, для поиска в списке:\n");
        if (scanf("%d", &year) != 1)
        {
            rc = ERR_NUMBER;
            goto exit;
        }

        need_data = create_auto("test", year, 0);
        if (!need_data)
        {
            rc = ERR_MEMORY_ALLOCATION;
            free_auto(need_data);
            goto exit;
        }

        find_el = find(head, need_data, comparator_by_year);
        if (find_el)
        {
            free_auto(need_data);
            printf("Найденный элемент:\n");
            print_auto(find_el->data);
            write_auto(find_el->data, file_output);
        }
        else
        {
            free_auto(need_data);
            rc = ERR_FIND;
            fclose(file_output);
            goto exit;
        }
    }
    else if (operation == OP_POP_FRONT)
    {
        auto_t *data = pop_front(&head);
        if (data == NULL)
        {
            fclose(file_output);
            rc = ERR_POP;
            goto exit;
        }

        printf("Удален элемент: ");
        print_auto(data);
        printf("\n");

        apply_list(head, print_auto);
        write_list(head, file_output);
        free_auto(data);
    }
    else if (operation == OP_COPY)
    {
        // Операция копирование
        node_t *new_head = NULL;
        printf("\n%sКопирование списка%s\n", GREEN, RESET);
        if ((rc = copy(head, &new_head)) != ERR_OK)
        {
            fclose(file_output);
            // free_list(new_head);
            goto exit;
        }
        apply_list(new_head, print_auto);
        write_list(new_head, file_output);
        free_list(new_head);
    }
    else if (operation == OP_SORT)
    {
        printf("\n----------------------------------\n\n");
        head = sort(head, comparator_by_price);
        if (head == NULL)
        {
            rc = ERR_HEAD;
            goto exit;
        }
        apply_list(head, print_auto);
        write_list(head, file_output);
    }
    else if (operation == OP_TASK)
    {
        // Решение задачи
        int year, price;
        if (argc != 6)
        {
            rc = ERR_ARGS_COUNT;
            goto exit;
        }
        if ((rc = string_to_int(argv[4], &year)) != ERR_OK)
        {
            goto exit;
        }
        if ((rc = string_to_int(argv[5], &price)) != ERR_OK)
        {
            goto exit;
        }
        printf("\n%sПоиск автомобилей не старше %d года и стоимостью менее %d%s\n", GREEN, year, price, RESET);
        node_t *task_head = filter(&head, year, price);
        if (task_head == NULL)
        {
            rc = ERR_EMPTY_OUTPUT;
            goto exit;
        }
        task_head = sort(task_head, comparator_by_price_and_year);
        if (task_head == NULL)
        {
            rc = ERR_EMPTY_OUTPUT;
            goto exit;
        }

        printf("%sРезультаты поиска:%s\n", GREEN, RESET);
        apply_list(task_head, print_auto);
        write_list(task_head, file_output);
        free_list(task_head);
    }
    fclose(file_output);
    exit:
    if (rc)
    {
        print_error_message(rc);
    }

    free_full(head);
    return rc;
}
