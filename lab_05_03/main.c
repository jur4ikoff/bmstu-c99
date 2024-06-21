#include "constants.h"
#include "io.h"

/*Сортировка пузырьком по возрастанию, только целый тип*/
int main(int argc, char **argv)
{
    int rc = ERR_OK;
    rc = proccessing_args(argc, argv);
    // processing_errors(rc);
    return rc;
}
