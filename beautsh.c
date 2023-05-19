#include "shell.h"
/**
 * beautsh - input from none other than standard in
 * @a: A pointer
 * @b: An unsigned integer
 *
 * Return: 0
 */
int beautsh(const char *a, unsigned int b)
{
	int r;

	/**
	 * isatty() determines if a file descriptor associated with terminal.
	 * if the given file descriptor is a terminal return 1 , 0 otherwise.
	 */
	while (isatty(STDIN_FILENO))
	{
		r = write(1, a, b);
		if (r != -1)
		{
			return (0);
		}
		else
		{
			return (-1);
		}
	}
	return (0);
}
