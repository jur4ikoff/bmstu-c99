# Функциональные тесты для ЛР 7
# Вариант сортировки - 5, вариант фильтрации - 3

## Позитивные тесты
| Номер | Описание                                             | Ввод                 | Вывод           |
| ----- | ---------------------------------------------------- | -------------------- | --------------- |
| 1     | Запуск без флага, сортировка массива из 7 элементов  | 10 2 3 -5 4 5 6      | -5 2 3 4 5 6 10 |
| 2     | Запуск                                               | 4 3 2 1 a            | 4               |
| 3     | Возрастающая последовательность длинее убывающей     | 1 2 3 4 3 2 a        | 4               |
| 4     | Убывающая последовательность длине возрастающей      | 2 3 4 3 2 1 0 a      | 5               |
| 5     | Присутствуют монотонные значения                     | 1 2 3 3 3 2 1 0 A    | 4               |
| 6     | Убывающая последовательность идет перед возрастающей | 4 3 2 1 0 1 2 3 4 5a | 6               |


## Негативные тесты
| Номер | Описание                 | Ввод | Вывод                    |
| ----- | ------------------------ | ---- | ------------------------ |
| 1     | Пустой файл              | ` `  | Empty sequence           |
| 2     | В файле нет чисел        | `c`  | Empty sequence           |
| 3     | Файл содержит одно число | `1`  | Sequence is not monotone |