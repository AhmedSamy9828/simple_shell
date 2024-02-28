#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *datash)
{
    int (*builtin)(data_shell *datash);

    /* Check if no command is provided */
    if (datash->args[0] == NULL)
        return (1); /* Return with success status */

    /* Get the function pointer to the built-in command */
    builtin = get_builtin(datash->args[0]);

    /* Check if the command is a built-in command */
    if (builtin != NULL)
        return (builtin(datash)); /* Execute the built-in command */

    /* Execute the command using cmd_exec function */
    return (cmd_exec(datash));
}
