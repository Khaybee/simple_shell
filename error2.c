#include "main.h"

/**
 * cd_error - error msg for the cd command in cd
 * @data: data relevant (directory)
 * Return: Error message
 */

char *cd_error(runtime_data *data)
{
	int len, len_id;
	char *error_checker, *str, *msg;

	str = int_to_string(data->lineCounter);
	if (data->tokens[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(data->tokens[1]);
	}

	len = _strlen(data->arguments[0] + _strlen(data->tokens[0]));
	len += _strlen(str) + _strlen(msg) + len_id + 5;
	error_checker = malloc(sizeof(char) * (len + 1));

	if (error_checker == 0)
	{
		free(str);
		return (NULL);
	}

	error_checker = strcat_cd(data, msg, error_checker, str);
	free(str);

	return (error_checker);
}

/**
 * strcat_cd - function that concatenates msg for cd _error
 *
 * @data: data relevant (directory)
 * @msg: msg to be print
 * @error_checker: output for msg
 * @str: counter lines
 * Return: error of msg.
 */
char *strcat_cd(runtime_data *data, char *msg, char *error_checker, char *str)
{
	char *not_legal;

	_strcpy(error_checker, data->arguments[0]);
	_strcat(error_checker, ": ");
	_strcat(error_checker, str);
	_strcat(error_checker, ": ");
	_strcat(error_checker, data->tokens[0]);
	_strcat(error_checker, msg);
	if (data->tokens[1][0] == '-')
	{
		not_legal = malloc(3);
		not_legal[0] = '-';
		not_legal[1] = data->tokens[1][1];
		not_legal[2] = '\0';
		_strcat(error_checker, not_legal);
		free(not_legal);
	}
	else
	{
		_strcat(error_checker, data->tokens[1]);
	}

	_strcat(error_checker, "\n");
	_strcat(error_checker, "\0");
	return (error_checker);
}
