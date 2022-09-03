#include "headers.h"

void changeDirectory(char *inputLine) {
    char *dir = (char *) malloc (MAX_INPUT * sizeof(char));
    dir = strtok(NULL, " ");

    char *arg2 = (char *) malloc (MAX_INPUT * sizeof(char));
    arg2 = strtok(NULL, " ");
    if (arg2 != NULL) {
        printf("Failed: cd: too many arguments\n");
        return;
    }

    if (dir == NULL) {
        chdir(HOME);
        strcpy(prevDir, cwd);
        /* getcwd(cwd, size); */
        strcpy(cwd, HOME);
    }
    else if (strcmp(dir, "-") == 0) {
        printf("%s\n", prevDir);
        chdir(prevDir);
        strcpy(prevDir, cwd);
        getcwd(cwd, size);
    }
    else if (strcmp(dir, "~") == 0) {
        chdir(HOME);
        strcpy(prevDir, cwd);
        getcwd(cwd, size);
    }
    else {
        if (chdir(dir) != 0) {
            perror("cd");
        }
        else {
            strcpy(prevDir, cwd);
            getcwd(cwd, size);
        }
    }
}

void echo(char *inputLine) {
    char *msg = (char *) malloc (MAX_INPUT * sizeof(char));
    msg = strtok(NULL, " ");
    while(msg != NULL) {
        printf("%s ", msg);
        msg = strtok(NULL, " ");
    }
    printf("\n");
}
