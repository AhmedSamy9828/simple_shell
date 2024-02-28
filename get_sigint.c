#include "shell.h"

/**
 * get_sigint - Handles the SIGINT signal (Ctrl + C) in the shell prompt.
 *              Prints a message to notify the user and re-prompts for input.
 * @sig: The signal number (unused).
 */
void get_sigint(int sig)
{
    // Suppress unused parameter warning
    (void)sig;

    // Print a message to notify the user about the SIGINT
    write(STDOUT_FILENO, "\n^-^ ", 5);
}
