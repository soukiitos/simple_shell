#include "shell.h"
/**
 * str - Print strings comparison
 * @s1: The first character
 * @s2: The second character
 *
 * Return: 0
 */
int str(char *s1, char *s2)
{
	int s = 0;

	while (s1[s] != '\0')
	{
		s++;
	}
	while (s2[s] != '\0')
	{
		s++;
		if (s1[s] == s2[s])
		{
			return (s1[s] + s2[s]);
		}
		else
		{
			return (s1[s] - s2[s]);
		}
	}
	return (0);
}

/**
 * _verpth - verify the built in
 * @args: The arguments
 * @i: An integer
 *
 * Return: 0
 */
int _verpth(char **args, int i)
{
	int b;
	char *bin[2] = {
		"exit",
		"env"
	};

	b = 0;
	if (b != 2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
	for (b = 0; b < 2; b++)
	{
		if (str(args[0], bin[b]) == 0)
		{
			break;
		}
	}
	if (str(bin[b], "exit") == 0)
	{
		free(args[0]);
		exit(i);
	}
	if (str(bin[b], "env") == 0)
	{
		if (ext_var == NULL)
		{
			return (0);
		}
		write(1, ext_var, 1000);
	}
	return (0);

}
