import ctypes as ct
import tkinter as tk
from tkinter import messagebox


PATH_TO_LIB = "./out/libmy_arr.so"
_shift_arr = _filter = None


def load_functions(lib):
    _shift_arr = lib.shift_arr
    _shift_arr.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t, ct.c_int)
    _shift_arr.restype = ct.c_int

    _filter = lib.filter
    _filter.argtypes = (
        ct.POINTER(ct.c_int),
        ct.POINTER(ct.c_int),
        ct.c_size_t,
        ct.POINTER(ct.c_int),
    )
    _filter.restype = ct.c_int
    return (_shift_arr, _filter)


def shift_arr(arr, shift: int):
    arr_len = len(arr)
    src = (ct.c_int * arr_len)(*arr)
    rc = _shift_arr(src, arr_len, shift)
    new_arr = list(src)
    return (rc, new_arr)


def filter(arr: list) -> tuple[int, list]:
    arr_len = len(arr)

    src = (ct.c_int * arr_len)(*arr)
    dst = ct.POINTER(ct.c_int)()
    src_len = ct.c_size_t(arr_len)
    dst_len = ct.c_int()

    rc = _filter(dst, src, src_len, ct.byref(dst_len))
    if rc != 0:
        return (rc, None)

    # print(dst_len.value)
    dst = (ct.c_int * arr_len)()
    # dst = (ct.c_int * dst_len.value)()
    rc = _filter(dst, src, src_len, ct.byref(dst_len))

    return (rc, dst)


def shift_handler():
    try:
        #breakpoint()
        # Получаем данные из полей ввода
        array_input = array_entry.get().strip()
        number_input = number_entry.get().strip()

        # Преобразуем строку в список чисел
        array = array_input.split(" ")
        array = [i for i in array if i]
        array = list(map(int, array))
        shift = int(number_input)

        # Поиск числа в массиве
        rc, res = shift_arr(array, shift)
        if (rc == 0):
            result_label.config(text=f"Результат: {" ".join(map(str, res))}")
        else:
            result_label.config(text=f"Неверные параметры")
    except ValueError:
        messagebox.showerror("Ошибка", "Пожалуйста, введите корректные данные.")

def filter_handler():
    try:
        # Получаем данные из полей ввода
        array_input = array_entry.get().strip()

        # Преобразуем строку в список чисел
        array = array_input.split(" ")
        array = [i for i in array if i]
        array = list(map(int, array))

        # Поиск числа в массиве
        rc, res = filter(array)
        if (rc == 0):
            result_label.config(text=f"Результат: {" ".join(map(str, res))}")
        else:
            result_label.config(text=f"Неверные параметры")
    except ValueError:
        messagebox.showerror("Ошибка", "Пожалуйста, введите корректные данные.")


if __name__ == "__main__":
    lib = ct.CDLL(PATH_TO_LIB)
    _shift_arr, _filter = load_functions(lib)

    # Создаем главное окно
    root = tk.Tk()
    root.title("Сдвиг массива влево и копирование полных квадратов")

    # Поле для ввода массива
    tk.Label(root, text="Введите массив через пробел:").pack()
    array_entry = tk.Entry(root, width=50)
    array_entry.pack()

    # Поле для ввода числа
    tk.Label(root, text="Введите сдвиг:").pack()
    number_entry = tk.Entry(root, width=50)
    number_entry.pack()

    # Label для вывода результата
    result_label = tk.Label(
        root, text="", wraplength=300
    )  # wraplength для переноса текста
    result_label.pack(pady=10)

    shift_button = tk.Button(root, text="Сдвиг массива влево", command=shift_handler)
    shift_button.pack(pady=5)

    # Кнопка очистки полей
    filter_button = tk.Button(root, text="Копирование элементов, которые являются полными квадратами", command=filter_handler)
    filter_button.pack(pady=5)

    # Запуск главного цикла приложения
    root.mainloop()
