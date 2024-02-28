#include "shell.h"

/**
 * swap_char - Swaps | and & for non-printed chars.
 *
 * @input: Input string.
 * @bool: Type of swap.
 * Return: Swapped string.
 */
char *swap_char(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|' && input[i + 1] != '|')
				input[i] = '\x10';  /* ASCII code for non-printed char */

			if (input[i] == '&' && input[i + 1] != '&')
				input[i] = '\f';  /* ASCII code for non-printed char */
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '\x10')
				input[i] = '|';  /* Restoring | */

			if (input[i] == '\f')
				input[i] = '&';  /* Restoring & */
		}
	}
	return (input);
}

/**
 * add_nodes - Adds separators and command lines to the lists.
 *
 * @head_s: Head of the separator list.
 * @head_l: Head of the command lines list.
 * @input: Input string.
 * Return: No return.
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';' || input[i] == '|' || input[i] == '&')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
			i++;
	}

	line = _strtok(input, ";|&");
	while (line != NULL)
	{
		line = swap_char(line, 1);
		add_line_node_end(head_l, line);
		line = _strtok(NULL, ";|&");
	}
}

/**
 * go_next - Moves to the next command line stored.
 *
 * @list_s: Separator list.
 * @list_l: Command line list.
 * @datash: Data structure.
 * Return: No return.
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep = 1;
	sep_list *ls_s = *list_s;
	line_list *ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if ((datash->status == 0 && (ls_s->separator == '&' || ls_s->separator == ';')) ||
			(datash->status != 0 && (ls_s->separator == '|' || ls_s->separator == ';')))
		{
			loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - Splits command lines according to separators ;, |, and & and executes them.
 *
 * @datash: Data structure.
 * @input: Input string.
 * Return: 0 to exit, 1 to continue.
 */
int split_commands(data_shell *datash, char *input)
{
	sep_list *head_s = NULL, *list_s;
	line_list *head_l = NULL, *list_l;
	int loop = 1;

	add_nodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loop = exec_line(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&head_s);
	free_line_list(&head_l);

	return loop;
}

/**
 * split_line - Tokenizes the input string.
 *
 * @input: Input string.
 * Return: Array of tokens.
 */
char **split_line(char *input)
{
	size_t bufsize = TOK_BUFSIZE;
	size_t i = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
	char *token;

	if (tokens == NULL)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[i] = token;

	while (token != NULL)
	{
		i++;

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, bufsize * sizeof(char *));
			if (tokens == NULL)
			{
				perror("Allocation error");
				exit(EXIT_FAILURE);
			}
		}

		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return tokens;
}

