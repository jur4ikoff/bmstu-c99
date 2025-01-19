# Практика темы "Динамические матрицы"

## 1. Матрица как одномерный массив
![alt text](pictures/1.png)
Представление в памяти
![alt text](pictures/2.png)

**Выделение памяти**
```c
err_t create_matrix(matrix_t *matrix, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = malloc(sizeof(int) * n * m);
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}
```

**Освобождение памяти**
```c
void free_matrix(matrix_t *matrix)
{
    if (matrix->matrix)
    {
        free(matrix->matrix);
    }
}
```

**Обращение к элементам**
```c
matrix.matrix[i * matrix.n + j]
```

### Примущества
- Простота выделения памяти
- Возможность использовать, как одномерный массив

### Недостатки
- Отладчик использованя памяти (valgrind) не может отследить обращение за пределы строки
- Нужно писать `[i * n + j]` – Нет синтаксического сахара

## 2. Матрица как массив указателей
Иной подход, мы выделяем память под массив указателей. В массиве будут храниться указатели на выделенные массивы для строк матрицы (массив)
![alt text](pictures/3.png)

Представление в памяти – указатель на массив хранится в стеке, все остальное в куче.
![alt text](pictures/4.png)

**Выделение памяти**
```c
err_t create_matrix(matrix_t *matrix, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = calloc((size_t)n, sizeof(int *)); // Юзаю calloc(), чтобы можно было спокойно сделать free(matrix->matrix[i])
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    for (size_t i = 0; i < (size_t)n; i++)
    {
        matrix->matrix[i] = calloc((size_t)m, sizeof(int));
        if (matrix->matrix[i] == NULL)
        {
            free_matrix(*matrix);
            return ERR_MEM_ALLOC;
        }
    }

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}
```

**Освобождение памяти**
```c
void free_matrix(matrix_t matrix)
{
    // Освобождаем все строки, потом освобождаем массив указателей
    if (matrix.matrix)
    {
        for (size_t i = 0; i < matrix.n; i++)
        {
            free(matrix.matrix[i]);
        }
        free(matrix.matrix);
    }
}
```

### Примущества
Исправляются недостатки предыдущего способа
- Можно обращаться к элементам a[i][j]
- Отладчики памяти `(valgrind)` могут отследить выход за пределы массива
- Можно обменять элементы с помощью обмена указателей
### Недостатки
- Используется бОльший объем памяти, чем при статическом выделении памяти, из-за того что нужно хранить массив указателей
- *(Из лекции) Сложность выделения и освобождения памяти (хз где сложность)*
- Память под матрицу не лежит одной областью

## Объеденение подходов 1
![alt text](pictures/5.png)
![alt text](pictures/6.png)


### Примущества
- Относительная простота выделения и освобождения
памяти. *(Я 10 минут пытался понять что происходит)*
- Возможность использовать как одномерный массив.
- Перестановка строк через обмен указателей. *(Из лекции) "Возможно ошибка"*
### Недостатки
- Относительная сложность начальной инициализации.
- Отладчик использования памяти не может отследить выход
за пределы строки.

**Выделение памяти**
```c
err_t create_matrix(matrix_t *matrix, int n, int m)
{
    int *data;
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = calloc((size_t)n, sizeof(int *)); // Юзаю calloc(), чтобы можно было спокойно сделать free(matrix->matrix[i])
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    data = calloc((size_t)n * (size_t)m, sizeof(int));
    if (data == NULL)
        return ERR_MEM_ALLOC;

    for (size_t i = 0; i < (size_t)n; i++)
    {
        matrix->matrix[i] = data + i * m;
    }

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}
```

**Освобождение памяти**
```c
void free_matrix(matrix_t matrix)
{
    // Освобождаем все строки, потом освобождаем массив указателей
    free(matrix.matrix[0]);
    free(matrix.matrix);
}
```

## Объеденение подходов 2
```
Алгоритм выделения памяти
Вход: количество строк (n) и количество столбцов (m)
Выход: указатель на массив строк матрицы (p)
• Выделить память под массив указателей на строки и
элементы матрицы (p)
• Обработать ошибку выделения памяти
• В цикле по количеству строк матрицы (0 <= i < n)
– Вычислить адрес i-ой строки матрицы (q)
– p[i]=q
```
### Примущества
- Простота выделение и освобождения памяти
- Возможность использования как одномерный массив
- Перестановка строк через обмен указателей
### Недостатки
- Относительная сложность начальное инициализации
- Отладчик не может отследить выход за пределы строки
  
**Выделение памяти**
```c
err_t create_matrix(matrix_t *matrix, int n, int m)
{
    if (n < 1 || m < 1)
    {
        return ERR_SIZE;
    }
    if (matrix == NULL)
        return ERR_ARGS;

    matrix->matrix = malloc((size_t)n * sizeof(int *) + n * m * sizeof(int)); // Юзаю calloc(), чтобы можно было спокойно сделать free(matrix->matrix[i])
    if (matrix->matrix == NULL)
        return ERR_MEM_ALLOC;

    for (size_t i = 0; i < (size_t)n; i++)
    {
        matrix->matrix[i] = (int *) ((char *)matrix->matrix + n * sizeof(int *) + i * m * sizeof(int)); // "биндим каждую строку"
    } 

    matrix->n = (size_t)n;
    matrix->m = (size_t)m;
    return ERR_OK;
}
```

**Освобождение памяти**
```c
void free_matrix(matrix_t matrix)
{
    free(matrix.matrix);
}
```
# Источники
1. Лекции МГТУ им Н.Э. Баумана, каф. Программная Инженерия.