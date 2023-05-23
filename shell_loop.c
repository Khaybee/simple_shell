#include "main.h"
/**
 * comment_out - removes comments from input
 * @str: input string
 * Return: input without comments
 */
char *comment_out(char *str)
{
	int a, b;

	b = 0;
	for (a = 0; str[a]; a++)
	{
		if (str[a] == '#')
		{
			if (a == 0)
			{
				free(str);
				return (NULL);
			}

			if (str[a - 1] == ' ' || str[a - 1] == '\t' || str[a - 1] == ';')
				b = a;
		}
	}
	if (b != 0)
	{
		str = _realloc(str, a, b + 1);
		str[b] = '\0';
	}
	return (str);
}

/**
 * shell_loop - main loop
 * @data: data structure
 */
void shell_loop(runtime_data *data)
{
	int loop, file;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = read_line(&file);
		if (file != -1)
		{
			input = comment_out(input);
			if (input == NULL)
				continue;
			if (syntax_error(data, input) == 1)
			{
				data->status = 2;
				free(input);
				continue;
			}
			input = replace_var(input, data);
			loop = split_cmd(data, input);
			data->lineCounter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * read_line - reads input in stdin
 * @file: value of the getline function
 * Return: input string
 */
char *read_line(int *file)
{
	char *inputs = NULL;
	size_t buffersize = 0;

	*file = getline(&inputs, &buffersize, stdin);

	return (inputs);
}
