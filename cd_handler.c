#include "main.h"

/**
 * cd_parent - changes to the parents directory
 *
 * @data: data relevants (environ)
 *
 * Return: no return
 */
void cd_parent(runtime_data *data)
{
	char *target_dir, *cp_current_dir, *cp_strtok_paswd;
	char current_dir[PATH_MAX];

	getcwd(current_dir, sizeof(current_dir));
	cp_current_dir = _strdup(current_dir);
	set_env("OLDPWD", cp_current_dir, data);
	target_dir = data->tokens[1];
	if (_strcmp(".", target_dir) == 0)
	{
		set_env("PWD", cp_current_dir, data);
		free(cp_current_dir);
		return;
	}
	if (_strcmp("/", cp_current_dir) == 0)
	{
		free(cp_current_dir);
		return;
	}
	cp_strtok_paswd = cp_current_dir;
	rev_str(cp_strtok_paswd);
	cp_strtok_paswd = _strtok(cp_strtok_paswd, "/");
	if (cp_strtok_paswd != NULL)
	{
		cp_strtok_paswd = _strtok(NULL, "\0");

		if (cp_strtok_paswd != NULL)
			rev_str(cp_strtok_paswd);
	}
	if (cp_strtok_paswd != NULL)
	{
		chdir(cp_strtok_paswd);
		set_env("PWD", cp_strtok_paswd, data);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data);
	}
	data->status = 0;
	free(cp_current_dir);
}


/**
 * cd_prev - changes to the previous directory
 *
 * @data: data relevant (environ)
 * Return: no return
 */


void cd_prev(runtime_data *data)
{
	char current_dir[PATH_MAX];
	char *p_current_dir, *p_old_dir, *cp_current_dir, *cp_old_dir;

	getcwd(current_dir, sizeof(current_dir));
	cp_current_dir = _strdup(current_dir);

	p_old_dir = _getenv("OLDPWD", data->_env);

	if (p_old_dir == NULL)
		cp_old_dir = cp_current_dir;
	else
		cp_old_dir = _strdup(p_old_dir);
	set_env("OLDPWD", cp_current_dir, data);

	if (chdir(cp_old_dir) == -1)
		set_env("PWD", cp_current_dir, data);
	else
		set_env("PWD", cp_old_dir, data);
	p_current_dir = _getenv("PWD", data->_env);

	write(STDOUT_FILENO, p_current_dir, _strlen(p_current_dir));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_current_dir);
	if (p_old_dir)
		free(cp_old_dir);

	data->status = 0;
	chdir(p_current_dir);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @data: data relevants (directories)
 * Return: no return
 */
void cd_to(runtime_data *data)
{
	char current_dir[PATH_MAX];
	char *target_dir, *cp_current_dir, *cp_target_dir;

	getcwd(current_dir, sizeof(current_dir));

	target_dir = data->tokens[1];
	if (chdir(target_dir) == -1)
	{
		get_error(data, 2);
		return;
	}

	cp_current_dir = _strdup(current_dir);
	set_env("OLDPWD", cp_current_dir, data);

	cp_target_dir = _strdup(target_dir);
	set_env("PWD", cp_target_dir, data);

	free(cp_current_dir);
	free(cp_target_dir);

	data->status = 0;
	chdir(target_dir);
}

/**
 * cd_home - changes to home directory
 *
 * @data: data relevants (environ)
 * Return: no return
 */
void cd_home(runtime_data *data)
{
	char *p_current_dir, *home;
	char current_dir[PATH_MAX];

	getcwd(current_dir, sizeof(current_dir));
	p_current_dir = _strdup(current_dir);

	home = _getenv("HOME", data->_env);

	if (home == NULL)
	{
		set_env("OLDPWD", p_current_dir, data);
		free(p_current_dir);
		return;
	}
	if (chdir(home) == -1)
	{
		get_error(data, 2);
		free(p_current_dir);
		return;
	}
	set_env("OLDPWD", p_current_dir, data);
	set_env("PWD", home, data);
	free(p_current_dir);
	data->status = 0;
}
