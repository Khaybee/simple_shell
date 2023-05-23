#include "main.h"

/**
 * char_dup - counts repetition of character in a word
 * @str: input string
 * @n: index
 * Return: repetition
 */
int char_dup(char *str, int n)
{
	if (*(str - 1) == *str)
		return (char_dup(str - 1, n + 1));

	return (n);
}

/**
 * find_syntax_error - finds synax error
 * @str: input string
 * @i: index
 * @last_char: last character read
 * Return: index of error
 */
int find_syntax_error(char *str, int i, char last_char)
{
	int count;

	count = 0;
	if (*str == '\0')
		return (0);
	if (*str == ' ' || *str == '\t')
		return (find_syntax_error(str + 1, i + 1, last_char));

	if (*str == ';')
		if (last_char == '|' || last_char == '&' || last_char == ';')
			return (i);
	if (*str == '|')
	{
		if (last_char == ';' || last_char == '&')
			return (i);

		if (last_char == '|')
		{
			count = char_dup(str, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}
	if (*str == '&')
	{
		if (last_char == ';' || last_char == '|')
			return (i);

		if (last_char == '&')
		{
			count = char_dup(str, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}
	return (find_syntax_error(str + 1, i + 1, *str));
}

/**
 * first_char - finds index of the first char
 * @str: input string
 * @n: indx
 * Return: 0 if successful else 1
 */
int first_char(char *str, int *n)
{
	for (*n = 0; str[*n]; *n += 1)
	{
		if (str[*n] == ' ' || str[*n] == '\t')
			continue;
		if (str[*n] == ';' || str[*n] == '|' || str[*n] == '&')
			return (-1);
		break;
	}
	return (0);
}
/**
 * syntax_error - finds and prints syntax error
 * @data: data structure
 * @str: input string
 * Return: 0 on success else 1
 */
int syntax_error(runtime_data *data, char *str)
{
	int a = 0, i = 0, start = 0;

	a = first_char(str, &start);
	if (a == -1)
	{
		print_syntax_error(data, str, start, 0);
		return (1);
	}

	i = find_syntax_error(str + start, 0, *(str + start));
	if (i != 0)
	{
		print_syntax_error(data, str, start + i, 1);
		return (1);
	}
	return (0);
}

/**
 * print_syntax_error - prints syntax error
 * @data: data structure
 * @str: input string
 * @n: index
 * @bol: control msg error
 */
void print_syntax_error(runtime_data *data, char *str, int n, int bol)
{
	char *msg, *msg_one, *msg_two, *error_msg, *count;
	int len;

	if (str[n] == ';')
	{
		if (bol == 0)
			msg = (str[n + 1] == ';' ? ";;" : ";");
		else
			msg = (str[n - 1] == ';' ? ";;" : ";");
	}

	if (str[n] == '|')
		msg = (str[n + 1] == '|' ? "||" : "|");
	if (str[n] == '&')
		msg = (str[n + 1] == '&' ? "&&" : "&");

	msg_one = ": Syntax erro: \"";
	msg_two = "\" unexpected\n";
	count = int_to_string(data->lineCounter);
	len = _strlen(data->arguments[0]) + _strlen(count);
	len += _strlen(msg) + _strlen(msg_one) + _strlen(msg_two) + 2;

	error_msg = malloc(sizeof(char) * (len + 1));
	if (error_msg == 0)
	{
		free(count);
		return;
	}
	_strcpy(error_msg, data->arguments[0]);
	_strcat(error_msg, ": ");
	_strcat(error_msg, count);
	_strcat(error_msg, msg_one);
	_strcat(error_msg, msg);
	_strcat(error_msg, msg_two);
	_strcat(error_msg, "\0");

	write(STDERR_FILENO, error_msg, len);
	free(error_msg);
	free(count);
}
