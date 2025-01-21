/*
необходимо реализовать стек на основе односвязного линейного списка
на вход подается строка из стдин,в которой особое значение имеют символы #
если встречается символ # то предыдущий символ удаляется из итоговой строки
если идут k символов # подряд то удаляются k символов перед ними
итоговоя строка ОБЯЗАТЕЛЬНО выводится в ‘…’
вход
A##B#HELLL#O

выход ‘HELLO’
*/

#include "constants.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_error_message(int rc)
{
    if (rc == ERR_EMPTY)
    {
        printf("ERR EMPTY\n");
    }
    else if (rc == ERR_INPUT)
    {
        printf("ERR INPUT\n");
    }
    else if (rc == ERR_MEMORY)
        printf("ERR MEMORY");
}

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN - 1, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_INPUT;

    *newline = 0;
    return ERR_OK;
}

int main(void)
{
    int rc = ERR_OK;
    char string[MAX_STRING_LEN];
    if ((rc = input_string(string)) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    if (strlen(string) < 1)
    {
        print_error_message(ERR_EMPTY);
        return ERR_EMPTY;
    }
    node_t *stack = NULL;
    convert_to_stack(&stack, string);

    size_t len = stack_len(stack);
    char *output = malloc(sizeof(char) * (len + 3));
    if (!output)
    {
        print_error_message(ERR_MEMORY);
        free_stack(stack);
        return ERR_MEMORY;
    }
    convert_to_string_reverse(stack, output, len + 3);
    printf("%s\n", output);

    free_stack(stack);
    free(output);
    return rc;
}
