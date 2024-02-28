#include "shell.h"

/**
 * without_comment - Deletes comments from the input.
 *
 * @input: Input string.
 * Return: Input without comments.
 */
char *without_comment(char *input)
{
	int i, last_valid_index;

	last_valid_index = 0;
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}

			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				last_valid_index = i;
		}
	}

	if (last_valid_index != 0)
	{
		input = _realloc(input, i, last_valid_index + 1);
		input[last_valid_index] = '\0';
	}

	return (input);
}

/**
 * shell_loop - Main loop of the shell.
 * @datash: Data relevant (argument vector, input, arguments).
 *
 * Return: No return.
 */
void shell_loop(data_shell *datash)
{
	int loop, eof_indicator;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&eof_indicator);
		if (eof_indicator != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
