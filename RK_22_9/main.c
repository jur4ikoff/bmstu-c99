#include "io.h"
#include "solve.h"
#include "constants.h"

int main(void)
{
    // Инициализация
    int rc = ERR_OK;
    struct subscriber_struct subscribers[MAX_STRINGS];
    size_t count = 0;
    char filename[MAX_STRING_LEN];

    // Ввод имени файла
    rc = input_string(filename, MAX_STRING_LEN, "Введите имя файла: ");
    if (rc != ERR_OK)
    {
        processing_errors(rc);
        return rc;
    }

    // Получение массива структур из файла
    rc = read_struct_from_file(filename, subscribers, &count);
    if (rc != ERR_OK)
    {
        processing_errors(rc);
        return rc;
    }

    // Обработка результата и вывод
    size_t output_count = 0;
    printf("Абоненты с фамилией, начинающейся на 'Иван':\n");
    for (size_t i = 0; i < count; i++)
    {
        if (strncmp(subscribers[i].surname, "Иван", 8) == 0)
        {
            printf("%s %s\n", subscribers[i].surname, subscribers[i].phone_number);
            output_count++;
        }
    }
    if (output_count == 0)
    {
        rc = ERR_EMPTY_OUTPUT;
        processing_errors(rc);
    }
    return rc;
}
