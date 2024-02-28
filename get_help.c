#include "shell.h"

/**
 * get_help - Retrieve help messages for built-in commands.
 *
 * This function retrieves help messages for built-in commands according to the
 * specified command name.
 *
 * @datash: Pointer to the data structure containing arguments and input.
 *
 * Return: Always returns 1.
 */
int get_help(data_shell *datash)
{
    /* Check if no specific command is specified */
    if (datash->args[1] == NULL)
        aux_help_general();
    /* Check if the specified command is "setenv" */
    else if (_strcmp(datash->args[1], "setenv") == 0)
        aux_help_setenv();
    /* Check if the specified command is "env" */
    else if (_strcmp(datash->args[1], "env") == 0)
        aux_help_env();
    /* Check if the specified command is "unsetenv" */
    else if (_strcmp(datash->args[1], "unsetenv") == 0)
        aux_help_unsetenv();
    /* Check if the specified command is "help" */
    else if (_strcmp(datash->args[1], "help") == 0)
        aux_help();
    /* Check if the specified command is "exit" */
    else if (_strcmp(datash->args[1], "exit") == 0)
        aux_help_exit();
    /* Check if the specified command is "cd" */
    else if (_strcmp(datash->args[1], "cd") == 0)
        aux_help_cd();
    /* Check if the specified command is "alias" */
    else if (_strcmp(datash->args[1], "alias") == 0)
        aux_help_alias();
    /* If the specified command is not recognized, print an error message */
    else
        write(STDERR_FILENO, datash->args[0], _strlen(datash->args[0]));

    /* Set the status to 0 indicating successful execution */
    datash->status = 0;
    return (1);
}

