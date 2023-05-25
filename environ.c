#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

#define BUFFER_SIZE 1024

int main(void)
{
	char command[BUFFER_SIZE];
	int status;

	while (1)
	{
		printf("$ "); // Display the prompt
		fflush(stdout); // Flush the output buffer

		// Read the user input
		if (fgets(command, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break; // End of file (Ctrl+D) condition
		}

		// Remove the trailing newline character
		command[strcspn(command, "\n")] = '\0';

		// Check if the user wants to exit
		if (strcmp(command, "exit") == 0)
			break;

		// Execute the command
		status = system(command);

		// Check if the command execution was successful
		if (status != 0)
			printf("Command execution failed\n");
	}

	return 0;
}
