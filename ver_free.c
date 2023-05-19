#include "shell.h"
/**
 * _verfree - Free memory
 * @c: A character
 *
 * Return: 0
 */
void _verfree(char *c)
{
	if (isatty(STDIN_FILENO) != 0)
	{
		free(c);
	}
	if (isatty(STDIN_FILENO))
	{
		_putchar('\n');
		free(c);
	}
}
