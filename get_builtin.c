#include "shell.h"

/**
 * get_builtin - Get the function pointer of a built-in command.
 *
 * This function returns the function pointer of the built-in command corresponding
 * to the given command name. If the command is not a built-in command, it returns NULL.
 *
 * @cmd: The command name.
 *
 * Return: Function pointer of the built-in command.
 */
int (*get_builtin(char *cmd))(data_shell *)
{
    /* Array of built-in commands with their corresponding function pointers */
    builtin_t builtin[] = {
        { "env", _env },
        { "exit", exit_shell },
        { "setenv", _setenv },
        { "unsetenv", _unsetenv },
        { "cd", cd_shell },
        { "help", get_help },
        { NULL, NULL } /* Termination entry */
    };
    int i;

    /* Iterate through the array to find the matching command */
    for (i = 0; builtin[i].name != NULL; i++)
    {
        if (_strcmp(builtin[i].name, cmd) == 0)
            break; /* Match found */
    }

    /* Return the function pointer of the matched built-in command */
    return (builtin[i].f);
}

