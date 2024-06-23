#include "solve.h"

/*Найти наибольшую длину монотонного фрагмента последовательности*/

int process(FILE *file, int *max_len)
{
    // Инициализация переменных
    int prev_number, current_number, max_len_increasing = 1, max_len_decreasing = 1, cur_len_increasing = 1, cur_len_decreasing = 1, is_increasing = 1;
    if (fscanf(file, "%d", &prev_number) != 1)
        return ERR_OUTPUT;

    size_t read = 1;
    while (fscanf(file, "%d", &current_number) == 1)
    {
        read++;
        // Если последовательность увеличивается
        if (current_number > prev_number)
        {
            // Обнуляем длину убывающей последовательности
            if (!is_increasing)
                cur_len_decreasing = 1;

            // Увеличиваем длину возрастающей последовательности
            cur_len_increasing++;
            is_increasing = 1;
        }
        else if (current_number < prev_number)
        {
            // Обнуляем длину возрастающей последовательности
            if (is_increasing)
                cur_len_increasing = 1;
            // Увеличаем длину убывающей последовательности
            cur_len_decreasing++;
            is_increasing = 0;
        }
        else
        {
            // Если последовательность не изменяется, то обнуляем длину последовательности
            cur_len_increasing = 1;
            cur_len_decreasing = 1;
            is_increasing = 1;
        }
        // Обновляем максимальную длину последовательности
        max_len_increasing = (cur_len_increasing > max_len_increasing) ? cur_len_increasing : max_len_increasing;
        max_len_decreasing = (cur_len_decreasing > max_len_decreasing) ? cur_len_decreasing : max_len_decreasing;

        prev_number = current_number;
    }

    // Вывод
    *max_len = (max_len_increasing > max_len_decreasing) ? max_len_increasing : max_len_decreasing;

    if (*max_len == 1)
        *max_len = 0;
    if (read <= 1)
        return ERR_SEQ;
    return ERR_OK;
}
