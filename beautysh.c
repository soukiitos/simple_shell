#include "shell.h"
/**
 * main - A beautiful code that passes the betty checks
 *
 * Return: 0
 */
int main(void)
{
	int i, j, k, l, m = 1;
	char *args[30], *c = NULL;
	size_t a;
	ssize_t b;

	b = getline(&c, &a, stdin);
	beautsh("$ ", 2);
	for (b = 0; b != -1; b++)
	{
		if (*c == '\n')
		{
			free(c);
		}
		else
		{
			_args(c, args);
			if (args[0] == NULL)
			{
				free(c);
			}
			else
			{
				j = com_exist(args[0]);
				if (j == 0)
				{
					i = execute(args), free(c);
				}
				else
				{
					l = _verth(args);
					if (!l)
					{
						k = _verpth(args, i);
						if (!k)
							i = not_exist(args, m), free(c);
					}
					else if (l == 0)
						i = execute(args), free(c), free(*args);
				}
			}
		}
		c = NULL, m++;
		beautsh("$ ", 2), b = getline(&c, &a, stdin);
	}
	_verfree(c);
	return (i);
}
