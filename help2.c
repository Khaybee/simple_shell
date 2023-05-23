#include "main.h"

/**
 * help - help information for builting str.
 * Return: Nothing
 */

void help(void)
{
	char *str = "Help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * cd_help - Help information for builtin alias.
 * Return: Nothing.
 */

void cd_help(void)
{
	char *str = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "\tChange the shell working directory. \n ";
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * alias_help - Help information for builtin  alias.
 * Return: Nothing.
 *
 */

void alias_help(void)
{
	char *str = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, str, _strlen(str));
}
