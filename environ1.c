#include "main.h"

/**
 * cmp_env_var - compares env variables names with the name passed.
 * @env_name: name of the environment variable.
 * @str: name passed.
 *
 * Return: 0 if not equal. Another value if they are.
 */

int cmp_env_var(const char *env_name, const char *str)
{
	int x;

	for (x = 0; env_name[x] != '='; x++)
	{
		if (env_name[x] != str[x])
		{
			return (0);
		}
	}
	return (x + 1);
}

/**
 * _getenv - get an environment variable
 * @str: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if it is found, else return NULL.
 */

char *_getenv(const char *str, char **_environ)
{
	char *ptr;
	int x, y;

	ptr = NULL;
	y = 0;
	for (x = 0; _environ[x]; x++)
	{
		y = cmp_env_var(_environ[x], str);
		if (y)
		{
			ptr = _environ[x];
			break;
		}
	}
	return (ptr + y);
}

/**
 * _env - prints the environment variables
 *
 * @data: data relevant
 * Return: 1 0n success.
 */

int _env(runtime_data *data)
{
	int a, b;

	for (a = 0; data->_env[a]; a++)
	{
		for (b = 0; data->_env[a][b]; b++)
			;

		write(STDOUT_FILENO, data->_env[a], b);
		write(STDOUT_FILENO, "\n", 1);
	}
	data->status = 0;

	return (1);
}
