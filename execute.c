#include "main.h"

/**
 * _execute - finds the builtins and commands
 *
 * @data: data relevants (tokens)
 * Return: 1 on success.
 */
int _execute(runtime_data *data)
{
	int (*builtin)(runtime_data *data);

	if (data->tokens[0] == NULL)
		return (1);

	builtin = get_builtin(data->tokens[0]);

	if (builtin != NULL)
		return (builtin(data));

	return (_exec(data));
}

/**
 * get_builtin - builtin that pais theiscommand in the arg
 * @command: command
 * Return: function pointer of this builtin command
 */
int (*get_builtin(char *command))(runtime_data *)
{
	builtin_cmd builtin[] = {
		{ "env", _env },
		{ "exit", __exit },
		{ "setenv", _setenv },
		{ "unsetenv", _unsetenv },
		{ "cd", _cd },
		{ "help", _help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, command) == 0)
			break;
	}

	return (builtin[i].f);
}
