# Определение путей к директориям с проектом
SRC_DIR := ./src
OUT_DIR := ./out
INC_DIR := ./inc

EXE_NAME := app.exe

# Настройки компиляции
CC := gcc
CFLAGS := -std=c99 -I $(INC_DIR)/ -Werror -Wall -pedantic -Wfloat-conversion -Wfloat-equal -Wvla -Wextra # Флаги компиляции по умоланию
LDFLAGS := -lm # Флаг линковки по умолчанию

cfiles := $(wildcard src/*.c)
obj_files := $(addprefix $(OUT_DIR)/, $(notdir $(cfiles:%.c=%.o)))

# Компиляция исходных файлов в объектные
$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Компоновка в исполняемый файл
$(EXE_NAME) : $(obj_files)
	$(CC) $(obj_files) -o $@ 

# Обозначение фиктивных целей
.PHONY : clean release debug asan msan ubsan coverage func unit myunit macunit

# Цель очистки
clean:
	$(RM) *.exe $(OUT_DIR)/*.o *.o *.out $(OUT_DIR)/*.gcno $(OUT_DIR)/*.gcda $(OUT_DIR)/*.d *.gcov

# Цель build release
release: CFLAGS += -DNDEBUG -g0
release: $(EXE_NAME)

# Цель build debug
debug: CFLAGS += -g3 -O0
debug: $(EXE_NAME)

