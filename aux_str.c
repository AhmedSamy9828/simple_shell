#include "shell.h"

/**
 * _strcat - Concatenate two strings.
 *
 * This function concatenates the string pointed to by src to the end of
 * the string pointed to by dest.
 *
 * @dest: Pointer to the destination string.
 * @src: Pointer to the source string.
 *
 * Return: Pointer to the destination string (dest).
 */
char *_strcat(char *dest, const char *src)
{
    int i;
    int j;

    /* Move to the end of the destination string */
    for (i = 0; dest[i] != '\0'; i++)
        ;

    /* Append the source string to the destination string */
    for (j = 0; src[j] != '\0'; j++)
    {
        dest[i] = src[j];
        i++;
    }

    /* Add null terminator to the end of the concatenated string */
    dest[i] = '\0';

    return (dest);
}


/**
 * *_strcpy - Copies the string pointed to by src.
 * @dest: Type char pointer the dest of the copied str
 * @src: Type char pointer the source of str
 * Return: the dest.
 */
char *_strcpy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}
/**
 * _strcmp - Function that compares two strings.
 * @s1: type str compared
 * @s2: type str compared
 * Return: Always 0.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i]; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}
/**
 * _strchr - locates a character in a string,
 * @s: string.
 * @c: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *_strchr(char *s, char c)
{
	unsigned int i = 0;

	for (; *(s + i) != '\0'; i++)
		if (*(s + i) == c)
			return (s + i);
	if (*(s + i) == c)
		return (s + i);
	return ('\0');
}

/**
 * _strspn - Get the length of a prefix substring.
 *
 * This function calculates the length of the initial segment of a string
 * that consists entirely of characters in another specified string.
 *
 * @s: Pointer to the initial segment.
 * @accept: Pointer to the accepted bytes.
 *
 * Return: The number of accepted bytes.
 */
int _strspn(char *s, char *accept)
{
    int i, j;
    int bool;

    /* Loop through the characters of the initial segment */
    for (i = 0; s[i] != '\0'; i++)
    {
        bool = 1;

        /* Check if the character is present in the accept string */
        for (j = 0; accept[j] != '\0'; j++)
        {
            if (s[i] == accept[j])
            {
                bool = 0; /* Character found in accept string */
                break;
            }
        }

        /* Break the loop if character not found in accept string */
        if (bool == 1)
            break;
    }

    /* Return the length of the prefix substring */
    return (i);
}

