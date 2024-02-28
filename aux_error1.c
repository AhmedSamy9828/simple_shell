#include "shell.h"

/**
 * strcat_cd - Function that concatenates the message for cd error
 *
 * @datash: Data relevant (directory)
 * @msg: Message to print
 * @error: Output message
 * @ver_str: Counter lines
 * Return: Error message
 */

char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	/* Copy program name */
	_strcpy(error, datash->av[0]);

	/* Concatenate separator */
	_strcat(error, ": ");

	/* Concatenate line counter */
	_strcat(error, ver_str);
	_strcat(error, ": ");

	/* Concatenate command name */
	_strcat(error, datash->args[0]);

	/* Concatenate error message */
	_strcat(error, msg);

	/* Check for illegal flag */
	if (datash->args[1][0] == '-')
	{
		/* Allocate memory for illegal flag */
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';

		/* Concatenate illegal flag */
		_strcat(error, illegal_flag);

		/* Free memory allocated for illegal flag */
		free(illegal_flag);
	}
	else
	{
		/* Concatenate directory name */
		_strcat(error, datash->args[1]);
	}

	/* Concatenate newline character */
	_strcat(error, "\n");

	/* Ensure null-termination of the string */
	_strcat(error, "\0");

	return (error);
}

/**
 * error_get_cd - error message for cd command in get_cd
 * @datash: data relevant (directory)
 * Return: Error message
 */
char *error_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datash->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datash: data relevant (counter, arguments)
 *
 * Return: Error message
 */

char *error_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	/* Convert counter to string */
	ver_str = aux_itoa(datash->counter);

	/* Calculate length of error message */
	length = _strlen(datash->av[0]) + _strlen(ver_str) +
	         _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;

	/* Allocate memory for error message */
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(ver_str);
		return (NULL);
	}

	/* Copy program name */
	_strcpy(error, datash->av[0]);

	/* Concatenate separator */
	_strcat(error, ": ");

	/* Concatenate line counter */
	_strcat(error, ver_str);
	_strcat(error, ": ");

	/* Concatenate command name */
	_strcat(error, datash->args[0]);

	/* Concatenate error message */
	_strcat(error, ": Illegal number: ");
	_strcat(error, datash->args[1]);

	/* Concatenate newline character */
	_strcat(error, "\n\0");

	/* Free memory allocated for counter string */
	free(ver_str);

	return (error);
}
