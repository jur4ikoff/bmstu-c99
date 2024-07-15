# Тесты черного ящика для РК2

## Негативные тесты
| №   | Описание                        | Ввод                                                                    | Вывод                  |
| --- | ------------------------------- | ----------------------------------------------------------------------- | ---------------------- |
| 1   | Пустой ввод                     | ` `                                                                     | Error, File not found  |
| 2   | Ввод несуществующего файла      | `test.txt`                                                              | Error, File not found  |
| 3   | Фамилия более 30 символов       | Ивановвввввввввввввввввввввв +7-900-123-45-67                           | Error, String overflow |
| 4   | Номер более 20 символов         | Иванов +7-900-123-45-675454545445454545                                 | Error, String overflow |
| 5   | Людей с фамилией на "Иван" нету | Ив +7-900-123-45-67 <br>нов +7-900-123-45-67<br>Петров +7-901-234-56-78 | Error, Empty output    |

## Позитивные тесты
| №   | Описание                               | Ввод                                                                           | Вывод                                               |
| --- | -------------------------------------- | ------------------------------------------------------------------------------ | --------------------------------------------------- |
| 1   | Один человек с фамилией на "Иван"      | Иван+7-900-123-45-67txt                                                        | Иван+7-900-123-45-67txt                             |
| 2   | Несколько человек с фамилией на "Иван" | Иван +7-900-123-45-67  <br> Иванов +7-900-123-45-67<br>Петров +7-901-234-56-78 | Иван +7-900-123-45-67  <br> Иванов +7-900-123-45-67 |
| 3   | Все люди с фамилией на "Иван"          | Иван +7-900-123-45-67  <br> Иванов +7-900-123-45-67                            | Иван +7-900-123-45-67  <br> Иванов +7-900-123-45-67 |