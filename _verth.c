#include "shell.h"
/**
 * _verth - verify the execution of the command
 * @args: arguments
 *
 * Return: 0
 */
int _verth(char **args)
{
	char *dir_p = NULL;
	char *command = NULL;
	char *glob_path = NULL;
	char *glob_reit = NULL;
	char *test[121];
	int i, j = -1;

	glob_path = get_envr("PATH");
	if (glob_path == NULL)
	{
		return (-1);
	}
	glob_reit = (reit_str(glob_path));
	dir_p = strtok(glob_reit, ":");
	if (dir_p == NULL)
	{
		return (-1);
	}
	free(glob_path);
	for (; j == -1 && dir_p != NULL; )
	{
		command = com_path(dir_p, args[0]);
		test[i] = command;
		j = com_exist(test[i]);
		dir_p = strtok(NULL, ":");
		i++;
	}
	i--;
	free(glob_reit);
	_free(test, i);
	if (j != 0)
	{
		free(test[i]);
		return (-1);
	}
	else
	{
		args[0] = test[i];
		return (0);
	}
}

