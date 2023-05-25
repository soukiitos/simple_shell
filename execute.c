#include "shell.h"
/**
 * execute - Execute commands
 * @args: The arguments
 *
 * Return: 0
 */
int execute(char **args)
{
	int e, f, g;
	char **ext_var = NULL;

	e = fork();
	if (e == 0)
	{
		f = execve(args[0], args, ext_var);
		/**
		 * execve() executes a process from another process.
		 * executes the file or executable which is specified in the path args.
		 */
		if (f != -1)
		{
			exit(0);
		}
		else
		{
			f = 126;
			/** perror() prints a descriptive error msg to stderr. */
			perror("hsh");
			exit(f);
		}
		exit(0);
	}
	else if (e == -1)
	{
		beautsh("not found\n", 7);
	}
	else
		wait(&g);
	/**
	 * wait () blocks the calling process until 1 of it's child processes exist
	 * or a signal recieved.
	 */
	/** WEXITSTATUS(status) a macro obtein exit status of a child process. */
	f = WEXITSTATUS(g);
	return (f);
}
