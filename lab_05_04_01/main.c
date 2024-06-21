#include "constants.h"
#include "io.h"
#include "args_realization.h"

// Бинарный файл, 1 и 3 номер задачи
int main(int argc, char **argv)
{
    int rc = ERR_OK;
    rc = processing_args(argc, argv);
    // processing_errors(rc);
    return rc;
}
