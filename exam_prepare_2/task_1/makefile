# Задаем директории
INC_DIR := ./inc 
SRC_DIR := ./src 
OUT_DIR := ./out

EXE_NAME := app.exe
CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -Wextra -I$(INC_DIR)/ -Wvla
LDFLAGS := -lm

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
obj_files := $(addprefix $(OUT_DIR)/, $(notdir $(SRC_FILES:.c=.o)))


$(EXE_NAME) : $(obj_files)
	$(CC) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY : clean
clean :
	$(RM) ./$(OUT_DIR)/*.o *.o ./$(OUT_DIR)/*.d *.d ./app.exe