#include "headers.h"

void changeDirectory(struct tokensInInput *tokenizedInput) {
    if (tokenizedInput->noOfTokens > 2) {
        printf("Failed: cd: too many arguments\n");
        return;
    }

    char *dir = tokenizedInput->tokens[1];

    if (dir == NULL) {
        chdir(HOME);
        strcpy(prevDir, cwd);
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
    char *msg;
    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        msg = tokenizedInput->tokens[i];
        printf("%s ", msg);
    }
    printf("\n");
}
