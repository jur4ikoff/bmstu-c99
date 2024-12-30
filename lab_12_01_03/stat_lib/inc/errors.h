#ifndef ERRORS_H_
#define ERRORS_H_

#define ERR_NOT_EQ -1
#define ERR_OK 0
#define ERR_ARGS 1
#define ERR_FILENAME 2
#define ERR_READ 3
#define ERR_ALLOCATION 4
#define ERR_EMPTY_INPUT 5
// #define ERR_WRITE 5
#define ERR_POINTER 6
#define ERR_LONG_ARRAY 7
#define ERR_EMPTY_OUTPUT 8

void print_err_msg(int arg);
#endif
