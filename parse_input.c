#include "headers.h"

struct tokensInInput *tokenizeInput(char *inputLine) {
    struct tokensInInput *tokenizedInput = (struct tokensInInput *)malloc(sizeof(struct tokensInInput));
    assert(tokenizedInput != NULL);

    tokenizedInput->noOfTokens = 0;

    tokenizedInput->tokens = (char **)malloc(MAX_INPUT * sizeof(char *));
    assert(tokenizedInput->tokens != NULL);

    char *token = strtok(inputLine, " ");
    while (token != NULL) {
        tokenizedInput->tokens[tokenizedInput->noOfTokens] = token;
        tokenizedInput->noOfTokens++;
        token = strtok(NULL, " ");
    }
    return tokenizedInput;
}

void parseInput(char *inputLine) {
    struct tokensInInput *tokenizedInput = tokenizeInput(inputLine);
    char *cmd = tokenizedInput->tokens[0];

    if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }
    if (strcmp(cmd, "cd") == 0) {
        changeDirectory(tokenizedInput);
    }
    else if (strcmp(cmd, "pwd") == 0) {
        printf("%s\n", cwd);
    }
    else if (strcmp(cmd, "echo") == 0) {
        echo(tokenizedInput);
    }
    else if (strcmp(cmd, "ls") == 0) {
        listFiles(tokenizedInput);
    }
    else if (strcmp(cmd, "history") == 0) {
        printHistory();
    }
    else if (strcmp(cmd, "pinfo") == 0) {
        pinfo(tokenizedInput);
    }
    else if (strcmp(cmd, "discover") == 0) {
        discover(tokenizedInput);
    }
    else {
        execute(tokenizedInput);
    }
}
