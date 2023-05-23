#include "main.h"
/**
 * _atoi - converts a string to an int
 * @str: input string
 * Return: ingeter
 */
int _atoi(char *str)
{
	int sign = 1, result = 0, i = 0;

	while (str[i] == ' ')
		i++;

	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}

	while (str[i] >= '0' && str[i] <= '9')
	{
		result =  (result * 10) + (str[i] - '0');
		i++;
	}

	return (sign * result);
}
/**
 * int_to_string - function that converts int to a string
 * @num: input number
 * Return: string
 */
char *int_to_string(int num)
{
	int len = 0, n = num, sign = 0, i;
	char *str;

	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	if (sign)
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	i = len - 1;
	while (n != 0)
	{
		str[i] = '0' + (n % 10);
		n /= 10;
		i--;
	}
	if (sign)
		str[0] = '-';
	str[len] = '\0';
	return (str);

}

/**
 * get_len - get length of a number
 * @num: input number
 * Return: length of the number
 */
int get_len(int num)
{
	unsigned int n;
	int len = 1;

	if (num < 0)
	{
		len++;
		n = num * -1;
	}
	else
	{
		n = num;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}
	return (len);
}
/**
 * _strtok - splits a string by delimiter
 * @str: string
 * @delimiter: delimiter
 * Return:tokenized string
 */
char *_strtok(char str[], const char *delimiter)
{
	char *start;
	static char *div, *end;
	unsigned int i, n;

	if (str != NULL)
	{
		if (_charscmp(str, delimiter))
			return (NULL);
		div = str;
		i = _strlen(str);
		end = &str[i];
	}
	start = div;
	if (start == end)
		return (NULL);

	for (n = 0; *div; div++)
	{
		if (div != start)
			if (*div && *(div - 1) == '\0')
				break;
		for (i = 0; delimiter[i]; i++)
		{
			if (*div == delimiter[i])
			{
				*div = '\0';
				if (div == start)
					start++;
				break;
			}
		}
		if (n == 0 && *div)
			n = 1;
	}
	if (n == 0)
		return (NULL);
	return (start);
}

/**
 * _charscmp - compare chars of a string
 * @str: input string
 * @delimiter: delimiter
 * Return: 1 if equal els 0
 */
int _charscmp(char str[], const char *delimiter)
{
	unsigned int i, j, match_count;

	for (i = 0, match_count = 0; str[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (str[i] == delimiter[j])
			{
				match_count++;
				break;
			}
		}
	}

	if (i == match_count)
		return (1);
	return (0);
}
