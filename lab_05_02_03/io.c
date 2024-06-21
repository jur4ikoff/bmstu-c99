#include "io.h"

// Обработка ошибок
void processing_errors(int exitcode)
{
    if (exitcode == ERR_EMPTY_INPUT)
        printf("Error, run program: example.exe <source file>\n");
    else if (exitcode == ERR_WRONG_INPUT)
        printf("Error, in file\n");
    else if (exitcode == ERR_FILE)
        printf("Error, File not exist\n");
    else if (exitcode == ERR_EMPTY_FILE)
        printf("Error, File is empty\n");
}
