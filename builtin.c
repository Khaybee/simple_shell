#include "main.h"

/**
 * _cd - changes the current directory.
 *
 * @data: relevant data.
 *
 * Return: relevant data.
 */

int _cd(runtime_data *data)
{
	char *directory;
	int is_home, is_home1, is_dash;

	directory = data->tokens[1];

	if (directory != NULL)
	{
		is_home = _strcmp("$HOME", directory);
		is_home1 = _strcmp("~", directory);
		is_dash = _strcmp("- -", directory);
	}

	if (directory == NULL || !is_home || !is_home1 || !is_dash)
	{
		cd_home(data);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_prev(data);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_parent(data);
		return (1);
	}

	cd_to(data);
	return (1);
}

/**
 * __exit - exits the shell
 *
 * @data: relevant data (status and tokens)
 * Return: 0 on success
 */

int __exit(runtime_data *data)
{
	int large_number, str_len, is_digit;
	unsigned int exit_status;

	if (data->tokens[1] != NULL)
	{
		exit_status = _atoi(data->tokens[1]);
		is_digit = _isdigit(data->tokens[1]);
		str_len = _strlen(data->tokens[1]);
		large_number = exit_status > (unsigned int)INT_MAX;

		if (!is_digit || str_len > 10 || large_number)
		{
			get_error(data, 2);
			data->status = 2;
			return (1);
		}
		data->status = (exit_status % 256);
	}
	return (0);
}

/**
 * _help - the function that retrieves help messages according to builtin
 * @data: the data structure (tokens and input)
 * Return: Always 0.
 */

int _help(runtime_data *data)
{
	if (data->tokens[1] == 0)
		general_help();
	else if (_strcmp(data->tokens[1], "setenv") == 0)
		setenv_help();
	else if (_strcmp(data->tokens[1], "env") == 0)
		env_help();
	else if (_strcmp(data->tokens[1], "unsetenv") == 0)
		unsetenv_help();
	else if (_strcmp(data->tokens[1], "help") == 0)
		help();
	else if (_strcmp(data->tokens[1], "exit") == 0)
		exit_help();
	else if (_strcmp(data->tokens[1], "cd") == 0)
		cd_help();
	else if (_strcmp(data->tokens[1], "alias") == 0)
		alias_help();
	else
		write(STDERR_FILENO, data->tokens[0],
				_strlen(data->tokens[0]));
	data->status = 0;
	return (1);
}
