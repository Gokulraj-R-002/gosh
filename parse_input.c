#include "headers.h"

void parseInput(char *inputLine) {
    char *cmd = (char *) malloc (MAX_INPUT * sizeof(char));
    cmd = strtok(inputLine, " ");

    if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }
    else if (strcmp(cmd, "cd") == 0) {
        changeDirectory(inputLine);
    }
    else if (strcmp(cmd, "pwd") == 0) {
        printf("%s\n", cwd);
    }
    else if (strcmp(cmd, "echo") == 0) {
        echo(inputLine);
    }
    else {
        int pid = fork();
        if (pid == 0) {
            if (execvp(cmd, NULL) == -1) {
                perror("execvp");
            }
        }
        else {
            wait(NULL);
        }
    }
}
