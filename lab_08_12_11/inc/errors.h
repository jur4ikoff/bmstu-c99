#ifndef ERRORS_H__
#define ERRORS_H__

#define OUTPUT 1

#define ERR_OK 0
#define ERR_ARG_COUNT 1
#define ERR_ARG_LENGTH 2
#define ERR_MEMORY_ALLOCATION 3
#define ERR_FILENAME 4
#define ERR_WRONG_MATRIX_SIZE 5
#define ERR_WRONG_MATRIX_ELEMENT 6
#define ERR_MATRIX_HAVE_NOT_EQ_SIZE 7
#define ERR_EMPTY_MATRIX 8
#define ERR_WRITE 9
#define ERR_MATRIX_CANNOT_MULT 10
#define ERR_WRONG_ACTION 11
#define ERR_NOT_SQUARE_MATRIX 12

void print_err_message(int arg);

#endif
