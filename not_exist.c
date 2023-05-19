#include "shell.h"
/**
 * not_exist - Print msg when the command doesn't exist
 * @args: The arguments
 * @m: An integer
 *
 * Return: 0
 */
int not_exist(char **args, int m)
{
	char *namesh = "hsh", *nonamesh = "./hsh";

	if (!isatty(STDIN_FILENO))
	{
		write(2, nonamesh, 5);
	}
	else
	{
		write(2, namesh, 3);
	}
	write(2, ": ", 2);
	err_msg(m);
	write(2, ": ", 2);
	write(2, args[0],msg_len(args[0]));
	write(2, ": not found\n", 12);
	/** The value 127 returned by /bin/sh when the command is not found. */
	return(127);
}
