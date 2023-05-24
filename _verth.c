#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
#define BUFFER_SIZE 256
#define PATH_DELIMITER ":"

int _verth(char *command, char **args);

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        char *path = getenv("PATH");
        char *path_token = strtok(path, PATH_DELIMITER);
        
        while (path_token != NULL) {
            char command_path[BUFFER_SIZE];
            snprintf(command_path, BUFFER_SIZE, "%s/%s", path_token, command);
            
            if (access(command_path, X_OK) == 0) {
                char *args[] = {command_path, NULL};
                _verth(command_path, args);
                exit(EXIT_SUCCESS);
            }
            
            path_token = strtok(NULL, PATH_DELIMITER);
        }
        
        /* Command not found */
        printf("Command '%s' not found.\n", command);
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(NULL);
    }
}

int _verth(char *command, char **args) {
    execvp(command, args);
    
    /* If execvp returns, an error occurred */
    perror("execvp() failed");
    exit(EXIT_FAILURE);
}

int main() {
    char command[BUFFER_SIZE];

    while (1) {
        printf("$ ");
        fgets(command, BUFFER_SIZE, stdin);

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue;
        }

        if (strcmp(command, "exit") == 0) {
            break;
        }
        
        /* Split the command into arguments */
        char *token;
        char *args[BUFFER_SIZE];
        int arg_count = 0;
        
        token = strtok(command, " ");
        while (token != NULL) {
            args[arg_count] = strdup(token);
            arg_count++;
            token = strtok(NULL, " ");
        }
        
        args[arg_count] = NULL;

        execute_command(args[0]);
        
        /* Free dynamically allocated memory for arguments */
        int i;
        for (i = 0; i < arg_count; i++) {
            free(args[i]);
        }
    }

    printf("Exiting shell...\n");

    return 0;
}
