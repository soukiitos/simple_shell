#include "shell.h"
/**
 * com_path - Print in global PATH
 * @dir_p: A directory
 * @com: The command
 *
 * Return: 0
 */
char *com_path(char *dir_p, char *com)
{
	char *command = NULL;
	int d, p, l1, l2;

	if (dir_p == NULL || com == NULL)
	{
		return (NULL);
	}
	l1 = msg_len(dir_p);
	l2 = msg_len(com);
	command = malloc(l1 + l2 + 2);
	if (command == NULL)
	{
		return (NULL);
	}
	for (d = 0; dir_p[d] != '\0'; d++)
	{
		command[d] = dir_p[d];
	}
	if (dir_p[d - 1] != '/')
	{
		command[d] = '/';
		d++;
	}
	for (p = 0; com[p] != '\0'; p++)
	{
		command[d + p] = com[p];
	}
	command[d + p] = '\0';
	return (command);
}
