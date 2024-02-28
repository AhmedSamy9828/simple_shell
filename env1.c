#include "shell.h"

/**
 * cmp_env_name - Compare environment variable names with the given name.
 *
 * This function compares the name of an environment variable with the
 * specified name to check if they are equal.
 *
 * @nenv: Name of the environment variable.
 * @name: Name passed for comparison.
 *
 * Return: 0 if the names are not equal, otherwise returns the length of
 * the name if they are equal.
 */
int cmp_env_name(const char *nenv, const char *name)
{
    int i;

    /* Iterate through the characters of the environment variable name */
    for (i = 0; nenv[i] != '='; i++)
    {
        /* Check if the characters are equal */
        if (nenv[i] != name[i])
        {
            return (0); /* Names are not equal */
        }
    }

    return (i + 1); /* Return the length of the name if equal */
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env are equal */
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{

		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);

}

