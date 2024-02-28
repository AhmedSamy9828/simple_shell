#include "shell.h"

/**
 * exit_shell - Exits the shell with the specified status.
 *
 * This function exits the shell with the specified status. If a status is provided
 * as an argument, it is used as the exit status. If no status is provided, the
 * default exit status is 0.
 *
 * @datash: Pointer to the data_shell structure containing status and arguments.
 *
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
    unsigned int ustatus; /* Status as an unsigned integer */
    int is_digit; /* Flag to check if argument is a digit */
    int str_len; /* Length of the argument */
    int big_number; /* Flag for checking if status is too large */

    /* Check if an exit status is provided as an argument */
    if (datash->args[1] != NULL)
    {
        /* Convert the argument to an unsigned integer */
        ustatus = _atoi(datash->args[1]);

        /* Check if the argument is a digit */
        is_digit = _isdigit(datash->args[1]);

        /* Get the length of the argument */
        str_len = _strlen(datash->args[1]);

        /* Check if the status is too large to fit into an int */
        big_number = ustatus > (unsigned int)INT_MAX;

        /* Check if the argument is not a digit, or if its length is too long, or if it's a big number */
        if (!is_digit || str_len > 10 || big_number)
        {
            /* Print error message for invalid exit status */
            get_error(datash, 2);

            /* Set shell status to indicate error */
            datash->status = 2;

            return (1); /* Return with failure status */
        }

        /* Set the shell status to the provided exit status */
        datash->status = (ustatus % 256);
    }

    return (0); /* Return with success status */
}

