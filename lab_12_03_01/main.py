import tkinter as tk
from tkinter import messagebox
import my_arr_lib

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
        # rc, res = shift_arr(array, shift)
        rc = my_arr_lib.shift_arr(array, shift)
        print(rc)
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
        #rc, res = filter(array)
        rc = 0
        res = array
        if (rc == 0):
            result_label.config(text=f"Результат: {" ".join(map(str, res))}")
        else:
            result_label.config(text=f"Неверные параметры")
    except ValueError:
        messagebox.showerror("Ошибка", "Пожалуйста, введите корректные данные.")


if __name__ == "__main__":
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
