#include "shell.h"

/**
 * check_env - Checks if the typed variable is an environment variable.
 *
 * @head: Pointer to the head of the linked list.
 * @input: Input string representing the variable.
 * @data: Pointer to the data structure containing environment variables.
 * Return: No return value.
 */
void check_env(r_var **head, char *input, data_shell *data)
{
	int row, chr, j, value_len;
	char **env_vars;

	env_vars = data->_environ;

	// Check each environment variable
	for (row = 0; env_vars[row]; row++)
	{
		// Compare characters of the input string with environment variables
		for (j = 1, chr = 0; env_vars[row][chr]; chr++)
		{
			if (env_vars[row][chr] == '=')
			{
				// Found a match, extract the value and add it to the list
				value_len = _strlen(env_vars[row] + chr + 1);
				add_rvar_node(head, j, env_vars[row] + chr + 1, value_len);
				return;
			}

			// Compare characters of the input with the current environment variable
			if (input[j] == env_vars[row][chr])
				j++;
			else
				break;
		}
	}

	// If no environment variable matches, add the input as a new variable
	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';' || input[j] == '\n')
			break;
	}

	// Add the variable to the list with a NULL value
	add_rvar_node(head, j, NULL, 0);
}


/**
 * check_vars - Check if the typed variable is $$ or $?
 *
 * @head: Pointer to the head of the linked list.
 * @input: Input string.
 * @status: Last status of the Shell.
 * @data: Pointer to the data structure.
 * Return: Number of characters processed.
 */
int check_vars(r_var **head, char *input, char *status, data_shell *data)
{
	int i, length_status, length_pid;

	length_status = _strlen(status);
	length_pid = _strlen(data->pid);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == '?')
			{
				// Add the last status to the list
				add_rvar_node(head, 2, status, length_status);
				i++;
			}
			else if (input[i + 1] == '$')
			{
				// Add the process ID to the list
				add_rvar_node(head, 2, data->pid, length_pid);
				i++;
			}
			else if (input[i + 1] == '\n' || input[i + 1] == '\0' || input[i + 1] == ' ' || input[i + 1] == '\t' || input[i + 1] == ';')
			{
				// Add NULL to the list for cases where $ is followed by newline, null character, space, tab, or semicolon
				add_rvar_node(head, 0, NULL, 0);
			}
			else
			{
				// Check if the variable is an environment variable
				check_env(head, input + i, data);
			}
		}
	}

	return (i);
}

/**
 * replaced_input - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
