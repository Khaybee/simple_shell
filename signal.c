#include "main.h"
/**
 * get_sigint - handles EOF prompt
 * @signal: signal for handler
 */
void get_sigint(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n$ ", 3);
}
