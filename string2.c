#include "main.h"
/**
 * _strchr - locates a character in a string
 * @str: string
 * @c: character
 * Return: pointer to first occurance of the character
 */
char *_strchr(char *str, char c)
{
	unsigned int n = 0;

	for (; *(str + n) != '\0'; n++)
		if (*(str + n) == c)
			return (str + n);
	if (*(str + n) == c)
		return (str + n);
	return ('\0');
}

/**
 * _strspn - get the length of a prefix substring
 * @str: string
 *
 * @s: accepted bytes
 * Return: the number of accepted bytes
 */
int _strspn(char *str, char *s)
{
	int x, y, bol;

	for (x = 0; *(str + x) != '\0'; x++)
	{
		bol = 1;
		for (y = 0; *(s + y) != '\0'; y++)
		{
			if (*(str + x) == *(s + y))
			{
				bol = 0;
				break;
			}
		}
		if (bol == 1)
			break;
	}
	return (x);
}

/**
 * _strcmp - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: always 0
 */
int _strcmp(char *str1, char *str2)
{
	int n;

	for (n = 0; str1[n] == str2[n] && str1[n]; n++)
		;

	if (str1[n] > str2[n])
		return (1);
	if (str1[n] < str2[n])
		return (-1);
	return (0);
}

/**
 * _isdigit - defines if a string passed is a number
 * @str: input string
 * Return: 1 if string is a number else 0
 */
int _isdigit(const char *str)
{
	unsigned int n;

	for (n = 0; str[n]; n++)
	{
		if (str[n] < 48 || str[n] > 57)
			return (0);
	}
	return (1);
}

/**
 * rev_str - reverses a string
 * @str: input string
 */
void rev_str(char *str)
{
	int counter = 0, x, y;
	char *s, z;

	while (counter >= 0)
	{
		if (str[counter] == '\0')
			break;
		counter++;
	}
	s = str;

	for (x = 0; x < (counter - 1); x++)
	{
		for (y = x + 1; y > 0; y--)
		{
			z = *(s + y);
			*(s + y) = *(s + (y - 1));
			*(s + (y - 1)) = z;
		}
	}
}
