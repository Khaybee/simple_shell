#include "main.h"

/**
 * copy_data - copies data to create new env or alias
 * @env_name: env var name (env or alias)
 * @env_val: env value (env or alias)
 *
 * Return: string of latest env or alias.
 */

char *copy_data(char *env_name, char *env_val)
{
	char *str;
	int name_len, val_len, len;

	name_len = _strlen(env_name);
	val_len = _strlen(env_val);
	len = name_len + val_len + 2;
	str = malloc(sizeof(char) * (len));
	_strcpy(str, env_name);
	_strcat(str, "=");
	_strcat(str, env_val);
	_strcat(str, "\0");

	return (str);
}

/**
 * set_env - sets the environment variable
 *
 * @name: name of environment variable
 * @env_val: value of environment variable
 * @data: data structure (environ)
 *
 * Return: Nothing.
 */

void set_env(char *name, char *env_val, runtime_data *data)
{
	int num;
	char *env_var, *env_name;

	for (num = 0; data->_env[num]; num++)
	{
		env_var = _strdup(data->_env[num]);
		env_name = _strtok(env_var, "=");

		if (_strcmp(env_name, name) == 0)
		{
			free(data->_env[num]);
			data->_env[num] = copy_data(env_name, env_val);
			free(env_var);
			return;
		}
		free(env_var);
	}
	data->_env = _reallocdp(data->_env, num, sizeof(char *) * (num + 2));
	data->_env[num] = copy_data(name, env_val);
	data->_env[num + 1] = NULL;
}

/**
 * _setenv - compares env variables names with the name passed
 * @data: relevant data (env name and value).
 * Return: 1 0n success.
 */

int _setenv(runtime_data *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	set_env(data->tokens[1], data->tokens[2], data);

	return (1);
}

/**
 * _unsetenv - dletes an environment variable
 * @data: data relevant (env name).
 *
 * Return: 1 on success.
 */

int _unsetenv(runtime_data *data)
{
	char **mem_env;
	char *env_var, *env_name;
	int x, y, z;

	if (data->tokens[1] == NULL)
	{
		get_error(data, -1);
		return (1);
	}
	z = -1;
	for (x = 0; data->_env[x]; x++)
	{
		env_var = _strdup(data->_env[x]);

		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, data->tokens[1]) == 0)
		{
			z = x;
		}
		free(env_var);
	}
	if (z == -1)
	{
		get_error(data, -1);
		return (1);
	}
	mem_env = malloc(sizeof(char *) * (x));
	for (x = y = 0; data->_env[x]; x++)
	{
		if (x != z)
		{
			mem_env[y] = data->_env[x];
			y++;
		}
	}
	mem_env[y] = NULL;
	free(data->_env[z]);
	free(data->_env);
	data->_env = mem_env;
	return (1);
}
