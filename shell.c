#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_CMD_LEN 100
#define MAX_ARGS 10

void execute_command(char *args[]) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {  // Child process
        execvp(args[0], args);
        perror("exec");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    char cmd[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    while (1) {
        printf("($) ");
        fflush(stdout);
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            break;
        }
        cmd[strcspn(cmd, "\n")] = '\0'; // remove trailing newline
        char *token = strtok(cmd, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the argument list
        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "cd") == 0) {
            if (chdir(args[1]) != 0) {
                perror("chdir");
            }
        } else {
            execute_command(args);
        }
    }
    return 0;
}
