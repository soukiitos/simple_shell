#include "shell.h"
/**
 * _args - An array of arguments
 * @c: A character
 * @args: A pointer
 *
 * Return: 0
 */
int _args(char *c, char **args)
{
	char *i, *j = c, *k;
	int a;

	k = strtok(c, "\n\t\r ");
	/** strtok() returns a pointer to the first token found in the string */
	a = 0;
	args[a] = k;
	for (a = 0; j != NULL; a++)
	{
		j = i;
		i = strtok(NULL, "\n\t\r ");
		args[a] = i;
	}
	args[a] = NULL;
	return (a);
}
