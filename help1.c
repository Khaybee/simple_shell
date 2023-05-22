#include "main.h"

/**
 * general_help - Entry point for str info for this str builtin
 * Return: no return
 */
void general_help(void)
{
	char *str = "$ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "These command are define internally.Type 'str' to see a list";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "Type 'str name' to finout more about the func 'name'.\n\n ";
	write(STDOUT_FILENO, str, _strlen(str));
	str = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "[dir]\nexit: exit [n]\n  env: env [option] [name=value] [command ";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "unsetenv [variable]\n";
	write(STDOUT_FILENO, str, _strlen(str));
}

/**
 * setenv_help - Help information for this builtin setenv
 * Return: no return
 */
void setenv_help(void)
{

	char *str = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "int replace)\n\t";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, str, _strlen(str));
}
/**
 * unsetenv_help - Help information for builtin unsetenv
 * Return: no return
 */
void unsetenv_help(void)
{
	char *str = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, str, _strlen(str));
}


/**
 * env_help - Help information for this builtin env
 * Return: no return
 */
void env_help(void)
{
	char *str = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, str, _strlen(str));

}

/**
 * exit_help - Help information for this builint exit
 * Return: no return
 */
void exit_help(void)
{
	char *str = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, str, _strlen(str));
	str = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, str, _strlen(str));
	str = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, str, _strlen(str));
}
