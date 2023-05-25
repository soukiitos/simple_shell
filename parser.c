#include "shell.h"

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    ssize_t input_length;
    char *command;

    while (1) {
        printf("$ ");
        fflush(stdout);

        // Read input from user
        input_length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (input_length == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Check for end of file (Ctrl+D)
        if (input_length == 0) {
            printf("\n");
            break;
        }

        // Remove newline character from input
        buffer[input_length - 1] = '\0';

        // Execute the command
        command = buffer;
        if (execvp(command, (char *[]){command, NULL}) == -1) {
            perror("execvp");
            printf("Command not found: %s\n", command);
        }
    }

    return 0;
}
