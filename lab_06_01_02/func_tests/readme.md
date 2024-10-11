# Функциональные тесты для 6 ЛР, вариант 2

## Позитивные тесты
| Номер | Описание                                                        | Аргументы                             | Ввод                                                                       | Вывод                                                                         |
| ----- | --------------------------------------------------------------- | ------------------------------------- | -------------------------------------------------------------------------- | ----------------------------------------------------------------------------- |
| 1     | Вывод 1 структуры                                               | ./func_tests/data/pos_01_in.txt ALL   | Banana<br>500<br>1200                                                      | Banana<br>500<br>1200                                                         |
| 2     | Сортировка 1 структуры                                          | ./func_tests/data/pos_02_in.txt       | Banana<br>500<br>1200                                                      | Banana<br>500<br>1200                                                         |
| 3     | Сортировка отсортированного массива структур                    | ./func_tests/data/pos_03_in.txt       | Banana<br>100<br>1200<br>Mango<br>400<br>1000<br>Water<br>1000<br>1000     | Banana<br>100<br>1200<br>Mango<br>400<br>1000<br>Water<br>1000<br>1000        |
| 4     | Сортировка массива структур отсортированного в обратном порядке | ./func_tests/data/pos_04_in.txt       | Water<br>1000<br>1000<br>Mango<br>400<br>1000<br>Banana<br>100<br>1000     | Banana<br>100<br>1000<br>Mango<br>400<br>1000<br>Water<br>1000<br>1000        |
| 5     | Сортировка неотсортированного массива структур                  | ./func_tests/data/pos_05_in.txt       | Banana<br>100<br>1000<br>Water<br>1000<br>1000<br>Mango<br>400<br>1000     | Banana<br>100<br>1000<br>Mango<br>400<br>1000<br>Water<br>1000<br>1000        |
| 6     | Вывод названия, который полностью совпадает с названием         | ./func_tests/data/pos_06_in.txt Water | Banana<br>100<br>1000<br>Water<br>1000<br>1000<br>Mango<br>400<br>1000     | Water<br>1000.000000<br>1000.000000                                           |
| 7     | Вывод названия, который неполностью совпадает с названием       | ./func_tests/data/pos_07_in.txt A     | Banana<br>100<br>1000<br>Apple<br>1000<br>1000<br>Americano<br>900<br>1000 | Apple<br>1000.000000<br>1000.000000<br>Americano<br>900.000000<br>1000.000000 |



## Негативные тесты
| Номер | Описание                                           | Аргументы                                           | Вывод                                |
| ----- | -------------------------------------------------- | --------------------------------------------------- | ------------------------------------ |
| 1     | Нет аргументов                                     | ./app.exe                                           | Error, wrong args count              |
| 2     | Слишком много аргументов                           | ./app.exe FILE [PREFIX] abc                         | Error, wrong args count              |
| 3     | Отсутствует файл ввода                             | ./app.exe FILE [PREFIX]                             | Error with input file                |
| 4     | Единственная структура введена не полностью        | ./app.exe ./func_tests_neg_04_in.txt                | Error, wrong args count              |
| 5     | Одна из структур введена не полностью              | ./app.exe ./func_tests_neg_05_in.txt                | Error in weight or volume of product |
| 6     | Пропущено поле при вводе структуры                 | ./app.exe ./func_tests_neg_06_in.txt                | Error in weight or volume of product |
| 7     | Переполнение массива структур                      | ./app.exe ./func_tests_neg_07_in.txt                | Error, overflow                      |
| 8     | Переполнение аргумента [PREFIX]                    | ./app.exe ./func_tests/data/neg_08_in.txt ALLLLL... | rror, overflow                       |
| 9     | Нет структуры, удовлетворяющей аргументу [PREFIX]  | ./app.exe ./func_tests/data/neg_09_in.txt TEST      | Error, empty output                  |
| 10    | Пустой файл                                        | ./app.exe ./func_tests/data/neg_10_in.txt           | Error name                           |
| 11    | Одно из числовых полей отрицательно                | ./app.exe ./func_tests/data/neg_11_in.txt           | Error number                         |
| 12    | При вычислении плотности происходит деление на 0   | ./app.exe ./func_tests/data/neg_12_in.txt           | Error number                         |
| 13    | Одно из чисел очень маленькое, близко к нулю 1e-64 | ./app.exe ./func_tests/data/neg_13_in.txt           | Error number                         |
| 14    | Имя стуктуры - пустая строка                       | ./app.exe ./func_tests/data/neg_14_in.txt           | Error name                           |