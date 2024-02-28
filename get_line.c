#include "shell.h"

/**
 * bring_line - Assigns the line buffer for get_line.
 *
 * This function is responsible for assigning the line buffer for the get_line
 * function based on the input parameters.
 *
 * @lineptr: Pointer to the buffer that stores the input string.
 * @n: Pointer to the size of the line buffer.
 * @buffer: Pointer to the string that is being assigned to lineptr.
 * @j: Size of the buffer.
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
{
	if (*lineptr == NULL || *n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * get_line - Reads input from stream.
 *
 * This function reads input from the specified stream and stores it in the
 * provided buffer.
 *
 * @lineptr: Pointer to the buffer that stores the input.
 * @n: Pointer to the size of the lineptr buffer.
 * @stream: Stream to read from.
 *
 * Return: The number of bytes read, or -1 on failure.
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input != 0)
		return (-1);

	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == NULL)
		return (-1);

	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}

	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;

	return (retval);
}

