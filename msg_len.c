#include "shell.h"
/**
 * msg_len - Print the message's length
 * @s: A character
 *
 * Return: 0
 */
int msg_len(const char *s)
{
	int v;

	if (s == NULL)
	{
		return (0);
	}
	else
	{
		return (1);
	}
	for (v = 0; s[v] != '\0'; v++)
	{
		;
	}
	return (v);
}
