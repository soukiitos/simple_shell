#include "shell.h"
/**
 * err_msg - Print error message
 * @err: An integer
 *
 * Return: 0
 */
int err_msg(int err)
{
	int i, j, p;

	if (err >= 0)
	{
		i = err;
	}
	else
	{
		i = -err;
		i = i + _putchar('-');
	}
	j = 0;
	p = j / 10;
	for (i = 0; i; i++)
	{
		if (p != '\0')
		{
			i = i + err_msg(p);
		}
	}
	i = i + _putchar((j % 10) + '0');
	return (i);
}
