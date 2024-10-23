# Код для построения графиков
# Использован фреймворк 'pandas' и библиотека matplotlib

import pandas as pd
import matplotlib.pyplot as plt

# Построение графика массива случайных элементов
df = pd.read_csv("random_arr.csv", delimiter=";")

plt.figure(figsize=(10, 6))
plt.grid(True)
plt.plot(df["size"], df["qsort"], label="qsort")
plt.plot(df["size"], df["mysort"], label="Модифицированная сортировка пузырьком")
plt.plot(
    df["size"], df["bublesort"], color="green", label="Обычная сортировка пузырьком"
)
plt.scatter(df["size"], df["qsort"], color="blue", s=2)
plt.scatter(df["size"], df["mysort"], color="orange", s=2)
plt.scatter(df["size"], df["bublesort"], color="green", s=2)
plt.xlabel("Размеры массива")
plt.ylabel("Время выполнения")
plt.title("Время сортировки рандомного массива")
plt.legend(loc="upper left")
plt.savefig("random_arr.svg")



# Построение графика массива отсортированного списка
df = pd.read_csv("sort_arr.csv", delimiter=";")

plt.figure(figsize=(10, 6))
plt.grid(True)
plt.plot(df["size"], df["qsort"], label="qsort")
plt.plot(df["size"], df["mysort"], label="Модифицированная сортировка пузырьком")
plt.plot(df["size"], df["bublesort"], color="green", label="Обычная сортировка пузырьком")
plt.scatter(df["size"], df["qsort"], color="blue", s=2)
plt.scatter(df["size"], df["mysort"], color="orange", s=2)
plt.scatter(df["size"], df["bublesort"], color="green", s=2)
plt.xlabel("Размеры массива")
plt.ylabel("Время выполнения")
plt.title("Время сортировки отсортированного массива")
plt.legend(loc="upper left")
plt.savefig("sort_arr.svg")


# Построение графика массива отсортированного в обратном порядке
df = pd.read_csv("reverse_sort_arr.csv", delimiter=";")

plt.figure(figsize=(10, 6))
plt.grid(True)
plt.plot(df["size"], df["qsort"], label="qsort")
plt.plot(df["size"], df["mysort"], label="Модифицированная сортировка пузырьком")
plt.plot(df["size"], df["bublesort"], color="green", label="Обычная сортировка пузырьком")
plt.scatter(df["size"], df["qsort"], color="blue", s=2)
plt.scatter(df["size"], df["mysort"], color="orange", s=2)
plt.scatter(df["size"], df["bublesort"], color="green", s=2)
plt.xlabel("Размеры массива")
plt.ylabel("Время выполнения")
plt.title("Время сортировки обратно отсортированного массива")
plt.legend(loc="upper left")
plt.savefig("reverse_sort_arr.svg")