#include "main.h"

/**
 * _strdup - duplicates a string
 * @s: string
 * Return: str
 */
char *_strdup(const char *s)
{
	char *str;
	size_t len;

	len = _strlen(s);
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	_memcpy(str, s, len + 1);
	return (str);
}
/**
 * _strlen - returns the length of a string
 * @s: input string
 * Return: return len
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}
/**
 * _memcpy - copy
 * @dest: destination
 * @src: source
 * @n: size
 * Return: destination
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *dest_ptr = (char *)dest;
	const char *src_ptr = (const char *)src;

	for (i = 0; i < n; i++)
		dest_ptr[i] = src_ptr[i];

	return (dest);
}
/**
 * _strcat - Concaternates two strings
 * @newstr: the new string
 * @str: string
 * Return: pointer to the con string
 */
char *_strcat(char *newstr, const char *str)
{
	char *ptr = newstr;

	while (*ptr != '\0')
		ptr++;
	while (*str != '\0')
	{
		*ptr = *str;
		ptr++;
		str++;
	}

	*ptr = '\0';
	return (newstr);
}

/**
 * _strcpy - copies a string
 * @newstr: new string
 * @str: string
 * Return: copied string
 */
char *_strcpy(char *newstr, char *str)
{
	size_t n;

	for (n = 0; str[n] != '\0'; n++)
		newstr[n] = str[n];
	newstr[n] = '\0';

	return (newstr);
}
