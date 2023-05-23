#include "main.h"

/**
 * swap_char - swaps | and & for the non-printed chars
 * @str: input string
 * @n: type of the swap
 * Return: swapped string
 */
char *swap_char(char *str, int n)
{
	int x;

	if (n == 0)
	{
		for (x = 0; str[x]; x++)
		{
			if (str[x] == '|')
			{
				if (str[x + 1] != '|')
					str[x] = 16;
				else
					x++;
			}

			if (str[x] ==  '&')
			{
				if (str[x + 1] != '&')
					str[x] = 12;
				else
					x++;
			}
		}
	}
	else
	{
		for (x = 0; str[x]; x++)
		{
			str[x] = (str[x] == 16 ? '|' : str[x]);
			str[x] = (str[x] == 12 ? '&' : str[x]);
		}
	}
	return (str);
}
/**
 * add_node - add separators and command lines in lists
 * @head_sep: head of the separator list
 * @head_line: head of the command lines list
 * @str: input string
 */
void add_node(separator_list **head_sep, cmd_list **head_line, char *str)
{
	int x;
	char *line;

	str = swap_char(str, 0);

	for (x = 0; str[x]; x++)
	{
		if (str[x] == ';')
			add_sep(head_sep, str[x]);

		if (str[x] == '|' || str[x] == '&')
		{
			add_sep(head_sep, str[x]);
			x++;
		}
	}

	line = _strtok(str, ";|&");
	do {
		line = swap_char(line, 1);
		add_line(head_line, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * _next - go to next command line
 * @list_sep: separator list
 * @list_ln: command line list
 * @data: data structure
 */
void _next(separator_list **list_sep, cmd_list **list_ln, runtime_data *data)
{
	int loop_sep;
	separator_list *separator;
	cmd_list *line;

	loop_sep = 1;
	separator = *list_sep;
	line = *list_ln;

	while (separator != NULL && loop_sep)
	{
		if (data->status == 0)
		{
			if (separator->sep == '&' || separator->sep == ';')
				loop_sep = 0;
			if (separator->sep == '|')
				line = line->next, separator = separator->next;
		}
		else
		{
			if (separator->sep == '|' || separator->sep == ';')
				loop_sep = 0;
			if (separator->sep == '&')
				line = line->next, separator = separator->next;
		}
		if (separator != NULL && !loop_sep)
			separator = separator->next;
	}

	*list_sep = separator;
	*list_ln = line;
}

/**
 * split_cmd - splits command line according to the separator
 * @data:data struct
 * @str: input string
 * Return: 0 to exit, 1 to continue
 */
int split_cmd(runtime_data *data, char *str)
{
	separator_list *head_sep, *list_sep;
	cmd_list *head_line, *list_line;
	int n;

	head_sep = NULL;
	head_line = NULL;

	add_node(&head_sep, &head_line, str);

	list_sep = head_sep;
	list_line = head_line;

	while (list_line != NULL)
	{
		data->input = list_line->line;
		data->tokens = tokenize(data->input);
		n = _execute(data);
		free(data->tokens);

		if (n == 0)
			break;

		_next(&list_sep, &list_line, data);

		if (list_line != NULL)
			list_line = list_line->next;
	}

	free_sep(&head_sep);
	free_line(&head_line);

	if (n == 0)
		return (0);
	return (1);
}

/**
 * tokenize - tokenize input string
 * @str: input string
 * Return: splitted string
 */
char **tokenize(char *str)
{
	size_t buffer_size;
	size_t x;
	char **tokens;
	char *token;

	buffer_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (buffer_size));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}
	token = _strtok(str, TOK_DELIM);
	tokens[0] = token;
	for (x = 1; token != NULL; x++)
	{
		if (x == buffer_size)
		{
			buffer_size += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, x, sizeof(char *) * buffer_size);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[x] = token;
	}
	return (tokens);
}
