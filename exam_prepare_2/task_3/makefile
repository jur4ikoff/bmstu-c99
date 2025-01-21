# Определение путей
SRC_DIR := ./src
OUT_DIR := ./out
INC_DIR := ./inc

CC := gcc
EXE_NAME := app.exe 

CFLAGS := -std=c99 -Wall -Werror -pedantic -Wfloat-conversion -Wvla -I$(INC_DIR)/
LDFLAGS := -lm

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OUT_FILES := $(addprefix $(OUT_DIR)/, $(notdir $(SRC_FILES:.c=.o)))

$(EXE_NAME) : $(OUT_FILES)
	$(CC) $(LDFLAGS) $^ -o $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY : clean
clean:
	$(RM) ./$(OUT_DIR)/*.o *.o ./$(OUT_DIR)/*.d *.d ./app.exe

debug: CFLAGS += -g3 -O0
debug: $(EXE_NAME)
