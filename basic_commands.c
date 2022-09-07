#include "headers.h"

void changeDirectory(struct tokensInInput *tokenizedInput) {
    /* char *dir = (char *) malloc (MAX_INPUT * sizeof(char)); */
    /* dir = strtok(NULL, " "); */

    /* char *arg2 = (char *) malloc (MAX_INPUT * sizeof(char)); */
    /* arg2 = strtok(NULL, " "); */
    /* if (arg2 != NULL) { */
    /*     printf("Failed: cd: too many arguments\n"); */
    /*     return; */
    /* } */
    if (tokenizedInput->noOfTokens > 2) {
        printf("Failed: cd: too many arguments\n");
        return;
    }

    char *dir = tokenizedInput->tokens[1];

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

void echo(struct tokensInInput *tokenizedInput) {
    /* char *msg = (char *) malloc (MAX_INPUT * sizeof(char)); */
    /* msg = strtok(NULL, " "); */
    char *msg;
    /* int i = 1; */
    /* while(msg != NULL) { */
    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        msg = tokenizedInput->tokens[i];
        printf("%s ", msg);
        /* i++; */
        /* msg = strtok(NULL, " "); */
    }
    printf("\n");
}
