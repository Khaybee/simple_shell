#include "main.h"

/**
 * assign_line - assigns the line var for the get_line
 * @lineptr: Buffer that store input str
 * @str: str which is being called to line
 * @ln_size: size of the line.
 * @buf_size: size of the buffer
 */

void assign_line(char **lineptr, size_t *ln_size, char *str, size_t buf_size)
{
	if (*lineptr == NULL)
	{
		if (buf_size > BUFSIZE)
		*ln_size = buf_size;

		else
			*ln_size = BUFSIZE;
		*lineptr = str;
	}
	else if (*ln_size < buf_size)
	{
		if (buf_size > BUFSIZE)
			*ln_size = buf_size;
		else
			*ln_size = BUFSIZE;
		*lineptr = str;
	}
	else
	{
		_strcpy(*lineptr, str);
		free(str);
	}
}

/**
 * _getline - Reads input from stream
 * @lineptr: buffer to store input
 * @size: size of bytes of input
 * @stream: stream to be read from
 *
 * Return: the number of characters read.
 */

ssize_t _getline(char **lineptr, size_t *size, FILE *stream)
{
	static ssize_t input;
	ssize_t val;
	char ch = 'z';
	char *str;
	int num;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	str = malloc(sizeof(char) * BUFSIZE);
	if (str == 0)
		return (-1);

	while (ch != '\n')
	{
		num = read(STDIN_FILENO, &ch, 1);
		if (num == -1 || (num == 0 && input == 0))
		{
			free(str);
			return (-1);
		}
		if (num == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			str = _realloc(str, input, input + 1);
		str[input] = ch;
		input++;
	}
	str[input] = '\0';
	assign_line(lineptr, size, str, input);
	val = input;
	if (num != 0)
		input = 0;
	return (val);
}
