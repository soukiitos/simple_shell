#include "shell.h"
/**
 * com_exist - 0 if the file exist
 * @path: the path
 *
 * Return: 0
 */
int com_exist(char *path)
{
	int j;

	j = open(path, O_RDONLY |  O_TRUNC);
	if (j == -1)
	{
		return (-1);
	}
	else
	{
		close(j);
		return (0);
	}
}
