#include "solve.h"

// Разделениие строки на лексемы и добавление их в соответствующие переменые структуры
int split_string(char *line, struct subscriber_struct *subscriber)
{
    char *token = strtok(line, " ");
    if (token != NULL)
    {
        if (strlen(token) >= (MAX_SURNAME_LEN))
        {
            return ERR_STRING_OWERFLOW;
        }
        strcpy(subscriber->surname, token);
        token = strtok(NULL, " ");
        if (token != NULL)
        {
            if (strlen(token) >= (MAX_STRING_LEN - MAX_SURNAME_LEN - 1))
            {
                return ERR_STRING_OWERFLOW;
            }
            strncpy(subscriber->phone_number, token, (MAX_STRING_LEN - MAX_SURNAME_LEN - 1));
        }
    }
    else
        return ERR_WHILE_READING;
    return ERR_OK;
}

// Чтения текстового файла и запись в структуру
int read_struct_from_file(char *filename, struct subscriber_struct *subscribers, size_t *count)
{
    // Инициализация переменных + открытие файла
    *count = 0;
    int rc = ERR_OK;
    char line[MAX_STRING_LEN];
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILE_NOT_FOUND;

    // Чтение из файла
    while (fgets(line, MAX_STRING_LEN - 1, file) && *count < MAX_STRINGS)
    {
        // Запись \0 вместо \n
        char *endline = strchr(line, '\n');
        if (!feof(file))
        {
            if (endline)
                *endline = '\0';
            else
                return ERR_STRING_OWERFLOW;
        }

        // Запись в структуру
        struct subscriber_struct subscriber;
        rc = split_string(line, &subscriber);
        if (rc != ERR_OK)
            return rc;
        subscribers[*count] = subscriber;
        (*count)++;
    }
    fclose(file);
    return rc;
}
