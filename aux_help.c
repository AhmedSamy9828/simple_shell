#include "shell.h"

/**
 * aux_help_env - Provides help information for the builtin command "env"
 *
 * This function displays usage information and examples for the "env" command.
 *
 * Return: This function does not return a value.
 */

void aux_help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));

}


/**
 * aux_help_setenv - Provides help information for the builtin command "setenv"
 *
 * This function displays usage information and examples for the "setenv" command.
 *
 * Return: This function does not return a value.
 */

void aux_help_setenv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void aux_help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_general - Entry point for help information for the help builtin
 * Return: no return
 */
void aux_help_general(void)
{
    char *help = "^-^ bash, version 1.0(1)-release\n";

    /* Write version message to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "These commands are defined internally. Type 'help' to see the list.\n";
    /* Write general information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "Type 'help name' to find out more about the function 'name'.\n\n ";
    /* Write additional information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = " alias: alias [name=['string']]\n";
    /* Write alias command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = " cd: cd [-L|[-P [-e]] [-@]] [dir]\n";
    /* Write cd command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "exit: exit [n]\n";
    /* Write exit command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "  env: env [option] [name=value] [command [args]]\n";
    /* Write env command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "  setenv: setenv [variable] [value]\n";
    /* Write setenv command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));

    help = "  unsetenv: unsetenv [variable]\n";
    /* Write unsetenv command information to stdout */
    write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * aux_help_exit - Help information fot the builint exit
 * Return: no return
 */
void aux_help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

