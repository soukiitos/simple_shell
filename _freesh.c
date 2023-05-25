#include "shell.h"
/**
 * _free - Free the memory
 * @d: A pointer
 * @e: An integer
 *
 * Return: 0
 */
void _free(char **d, int e)
{
	int f;

	for (f = 0; f < e; f++)
	{
		free(d[f]);
	}
	if (d == NULL)
	{
		return;
	}
}
