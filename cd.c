#include "shell.h"

/**
 * cd_dot - Change directory to the parent directory.
 *
 * This function changes the current directory to its parent directory.
 *
 * @datash: Pointer to the data relevant (environment).
 *
 * Return: No return.
 */
void cd_dot(data_shell *datash)
{
    char current_dir[PATH_MAX];
    char *old_pwd;
    char *new_pwd;
    char *dir_token;

    getcwd(current_dir, sizeof(current_dir));
    old_pwd = _strdup(current_dir);
    set_env("OLDPWD", old_pwd, datash);

    if (_strcmp(".", datash->args[1]) == 0)
    {
        set_env("PWD", old_pwd, datash);
        free(old_pwd);
        return;
    }

    if (_strcmp("/", current_dir) == 0)
    {
        free(old_pwd);
        return;
    }

    new_pwd = _strdup(old_pwd);
    dir_token = strtok(new_pwd, "/");
    while (dir_token != NULL)
    {
        chdir("..");
        dir_token = strtok(NULL, "/");
    }

    getcwd(current_dir, sizeof(current_dir));
    set_env("PWD", current_dir, datash);
    datash->status = 0;

    free(old_pwd);
    free(new_pwd);
}

void cd_to(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}


/**
 * cd_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}

