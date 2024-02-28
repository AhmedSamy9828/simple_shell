#include "shell.h"

/**
 * repeated_char - Count the repetitions of a character.
 *
 * This function recursively counts the number of repetitions of a character
 * at a specific index in a string.
 *
 * @input: Pointer to the input string.
 * @i: Index of the character in the string.
 *
 * Return: Number of repetitions.
 */
int repeated_char(char *input, int i)
{
    /* Check if the previous character is equal to the current character */
    if (*(input - 1) == *input)
        return (repeated_char(input - 1, i + 1)); /* Recursively count repetitions */

    return (i); /* Return the count of repetitions */
}

/**
 * error_sep_op - Find syntax errors related to separators.
 *
 * This function recursively checks the input string for syntax errors
 * related to separators (;, |, &).
 *
 * @input: Pointer to the input string.
 * @i: Current index in the input string.
 * @last: Last character read.
 *
 * Return: Index of the error, or 0 if there are no errors.
 */
int error_sep_op(char *input, int i, char last)
{
    int count;

    /* Base case: End of string reached */
    if (*input == '\0')
        return (0);

    /* Skip whitespaces */
    if (*input == ' ' || *input == '\t')
        return (error_sep_op(input + 1, i + 1, last));

    /* Check for syntax errors */
    if (*input == ';')
    {
        if (last == '|' || last == '&' || last == ';')
            return (i);
    }
    else if (*input == '|')
    {
        if (last == ';' || last == '&')
            return (i);

        if (last == '|')
        {
            count = repeated_char(input, 0);
            if (count == 0 || count > 1)
                return (i);
        }
    }
    else if (*input == '&')
    {
        if (last == ';' || last == '|')
            return (i);

        if (last == '&')
        {
            count = repeated_char(input, 0);
            if (count == 0 || count > 1)
                return (i);
        }
    }

    /* Move to the next character in the input string */
    return (error_sep_op(input + 1, i + 1, *input));
}

