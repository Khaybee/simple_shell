#include "main.h"


/**
 * is_exec - determines if this is an executable
 *
 * @data: data structure
 * Return: 0 if this is not an executable, other number if it does
 */
int is_exec(runtime_data *data)
{
	struct stat _stat;
	char *input_str;
	int i;

	input_str = data->tokens[0];
	for (i = 0; input_str[i]; i++)
	{
		if (input_str[i] == '.')
		{
			if (input_str[i + 1] == '.')
				return (0);
			if (input_str[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input_str[i] == '/' && i != 0)
		{
			if (input_str[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input_str + i, &_stat) == 0)
	{
		return (i);
	}
	get_error(data, 127);
	return (-1);
}


/**
 * _which - locate a command
 *
 * @command: command name
 * @_environ: environment of variable
 * Return: location of this command.
 */
char *_which(char *command, char **_environ)
{
	int dir_len, cmd_len, i;
	char *path, *ptr_path, *token_path, *dir;
	struct stat _stat;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		cmd_len = _strlen(command);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_currentdir(path, &i))
				if (stat(command, &_stat) == 0)
					return (command);
			dir_len = _strlen(token_path);
			dir = malloc(dir_len + cmd_len + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, command);
			_strcat(dir, "\0");
			if (stat(dir, &_stat) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(command, &_stat) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &_stat) == 0)
			return (command);
	return (NULL);
}



/**
 * is_currentdir - checks ":" if is in this current directory.
 * @path: type char pointer char.
 * @n: type int pointer of the index.
 * Return: 1 if the path is a searchable in the cd, 0 otherwise.
 */
int is_currentdir(char *path, int *n)
{
	if (path[*n] == ':')
		return (1);

	while (path[*n] != ':' && path[*n])
	{
		*n += 1;
	}

	if (path[*n])
		*n += 1;

	return (0);
}



/**
 * check_error - verifies if the user has permissions to access
 *
 * @directory: destination of directory
 * @data: data structure
 * Return: 1 if the was an error, 0 if not
 */
int check_error(char *directory, runtime_data *data)
{
	if (directory == NULL)
	{
		get_error(data, 127);
		return (1);
	}

	if (_strcmp(data->tokens[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			get_error(data, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(data->tokens[0], X_OK) == -1)
		{
			get_error(data, 126);
			return (1);
		}
	}

	return (0);
}


/**
 * _exec - executes command line
 *
 * @data: data relevant (args and input)
 * Return: 1 on success.
 */
int _exec(runtime_data *data)
{
	pid_t process;
	pid_t pid;
	int status;
	char *dir;
	int execute;
	(void) process;

	execute = is_exec(data);
	if (execute == -1)
		return (1);
	if (execute == 0)
	{
		dir = _which(data->tokens[0], data->_env);
		if (check_error(dir, data) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execute == 0)
			dir = _which(data->tokens[0], data->_env);
		else
			dir = data->tokens[0];
		execve(dir + execute, data->tokens, data->_env);
	}
	else if (pid < 0)
	{
		perror(data->arguments[0]);
		return (1);
	}
	else
	{
		do {
			process = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	data->status = status / 256;
	return (1);
}
