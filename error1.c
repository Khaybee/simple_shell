#include "main.h"

/**
 * get_error - calls this error according the builtin, syntax or permission
 * @data: data structure that carries arguments
 * @val_error: error for value
 * Return: error
 */
int get_error(runtime_data *data, int val_error)
{
	char *error_checker;

	switch (val_error)
	{
		case -1:
			error_checker = env_error(data);
			break;

		case 126:
			error_checker = error_path(data);
			break;
		case 127:
			error_checker = command_not_found(data);
			break;
		case 2:
			if (_strcmp("exit", data->tokens[0]) == 0)
				error_checker = exit_error(data);
			else if (_strcmp("cd", data->tokens[0]) == 0)
				error_checker = cd_error(data);
			break;
	}

	if (error_checker)
	{
		write(STDERR_FILENO, error_checker, _strlen(error_checker));
		free(error_checker);
	}

	data->status = val_error;
	return (val_error);
}

/**
 * exit_error - generic error msg for the exit in get_exit
 * @data: data relevant (linecounter, tokens)
 *
 * Return: Error for msg
 */

char *exit_error(runtime_data *data)
{
	int len;
	char *error_checker;
	char *str;

	str = int_to_string(data->lineCounter);
	len = _strlen(data->arguments[0]) + _strlen(str);
	len += _strlen(data->tokens[0]) + _strlen(data->tokens[1]) + 23;
	error_checker = malloc(sizeof(char) * (len + 1));
	if (error_checker == 0)
	{
		free(str);
		return (NULL);
	}
	_strcpy(error_checker, data->arguments[0]);
	_strcat(error_checker, ": ");
	_strcat(error_checker, str);
	_strcat(error_checker, ": ");
	_strcat(error_checker, data->tokens[0]);
	_strcat(error_checker, ": Illegal number: ");
	_strcat(error_checker, data->tokens[1]);
	_strcat(error_checker, "\n\0");
	free(str);

	return (error_checker);
}

/**
 * command_not_found - generic error msg for the command not found
 * @data: data relevants (counter, arguments)
 * Return: Error msg
 */
char *command_not_found(runtime_data *data)
{
	int len;
	char *error_checker;
	char *str;

	str = int_to_string(data->lineCounter);
	len = _strlen(data->arguments[0]) + _strlen(str);
	len += _strlen(data->tokens[0]) + 16;
	error_checker = malloc(sizeof(char) * (len + 1));
	if (error_checker == 0)
	{
		free(error_checker);
		free(str);
		return (NULL);
	}
	_strcpy(error_checker, data->arguments[0]);
	_strcat(error_checker, ": ");
	_strcat(error_checker, str);
	_strcat(error_checker, ": ");
	_strcat(error_checker, data->tokens[0]);
	_strcat(error_checker, ": not found\n");
	_strcat(error_checker, "\0");
	free(str);
	return (error_checker);
}


/**
 * env_error - error msg for this env in get_env.
 * @data: data for relevants (counter, arguments)
 * Return: error_checker for the msg.
 */
char *env_error(runtime_data *data)
{
	int len;
	char *error_checker;
	char *str;
	char *msg;

	str = int_to_string(data->lineCounter);
	msg = ": Unable to add/remove from environment\n";
	len = _strlen(data->arguments[0]) + _strlen(str);
	len += _strlen(data->tokens[0]) + _strlen(msg) + 4;
	error_checker = malloc(sizeof(char) * (len + 1));
	if (error_checker == 0)
	{
		free(error_checker);
		free(str);
		return (NULL);
	}

	_strcpy(error_checker, data->arguments[0]);
	_strcat(error_checker, ": ");
	_strcat(error_checker, str);
	_strcat(error_checker, ": ");
	_strcat(error_checker, data->tokens[0]);
	_strcat(error_checker, msg);
	_strcat(error_checker, "\0");
	free(str);

	return (error_checker);
}
/**
 * error_path - error sms for path and failure denied permission.
 * @data: data the relevants (counter, arguments).
 *
 * Return: The error_checker for the string.
 */
char *error_path(runtime_data *data)
{
	int len;
	char *str;
	char *error_checker;

	str = int_to_string(data->lineCounter);
	len = _strlen(data->arguments[0]) + _strlen(str);
	len += _strlen(data->tokens[0]) + 24;
	error_checker = malloc(sizeof(char) * (len + 1));
	if (error_checker == 0)
	{
		free(error_checker);
		free(str);
		return (NULL);
	}
	_strcpy(error_checker, data->arguments[0]);
	_strcat(error_checker, ": ");
	_strcat(error_checker, str);
	_strcat(error_checker, ": ");
	_strcat(error_checker, data->tokens[0]);
	_strcat(error_checker, ": Permission denied\n");
	_strcat(error_checker, "\0");
	free(str);
	return (error_checker);
}
