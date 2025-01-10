SRC_DIR := ./src
INC_DIR := ./inc
OUT_DIR := ./out

EXE_NAME := app.exe # Имя исходника
CC := gcc # Компилятор
CFLAGS := -std=c99 -I $(INC_DIR)/ -Wextra -Wall -Werror -pedantic -Wfloat-conversaition -Wvla # Флаги комплиции по умолчанию 
LDFLAGS := -lm

$(EXE_NAME) : $(OUT_DIR)/main.o $(OUT_DIR)/test.o
	$(CC) $(OUT_DIR)/main.o $(OUT_DIR)/test.o $(LDFLAGS) -o $(EXE_NAME)

$(OUT_DIR)/main.o : $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c $(OUT_DIR)/main.o
# Задаем фоновые цели
.PHONY : clean

# Цель очистки
clean: 
	$(RM) ./$(OUT_DIR)/*.o .o ./$(OUT_DIR)/*.d .d