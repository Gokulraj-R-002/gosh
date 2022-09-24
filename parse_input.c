#include "headers.h"

int isIORedirection = 0;
int ioRedirPos = 0;

void convertTabsIntoSpaces(char *inputLine) {
    for (int i = 0; i < strlen(inputLine); i++) {
        if (inputLine[i] == '\t') {
            inputLine[i] = ' ';
        }
    }
}

struct tokensInInput *tokenizeInput(char *inputLine, char *delim) {
    struct tokensInInput *tokenizedInput = (struct tokensInInput *)malloc(sizeof(struct tokensInInput));
    assert(tokenizedInput != NULL);

    tokenizedInput->noOfTokens = 0;

    tokenizedInput->tokens = (char **)malloc(MAX_INPUT * sizeof(char *));
    assert(tokenizedInput->tokens != NULL);

    char *token = strtok(inputLine, delim);
    while (token != NULL) {
        tokenizedInput->tokens[tokenizedInput->noOfTokens] = token;
        tokenizedInput->noOfTokens++;
        token = strtok(NULL, delim);
    }
    return tokenizedInput;
}

void searchCommand(struct tokensInInput *tokenizedInput) {
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

void parseInput(char *inputLine) {
    convertTabsIntoSpaces(inputLine);

    int isBgProcess = 0;
    int noOfCommands = 0;

    /* struct tokensInInput *tokenizedWrtSemiCol = tokenizeInput(inputLine, ";"); */
    /* for (int i = 0; i < tokenizedWrtSemiCol->noOfTokens; i++) { */
    /*     char *token1 = tokenizedWrtSemiCol->tokens[i]; */
    /*     struct tokensInInput *tokenizedWrtAmpersand = tokenizeInput(token1, "&"); */
    /*     noOfCommands += tokenizedWrtAmpersand->noOfTokens; */
    /*     /1* for (int j = 0; j < tokenizedWrtAmpersand->noOfTokens; j++) { *1/ */
    /*     /1*     printf("%s\n", tokenizedWrtAmpersand->tokens[j]); *1/ */
    /*     /1* } *1/ */
    /* } */
    /* printf("noOfCommands: %d\n", noOfCommands); */

    /* for (int i = 0; i < strlen(inputLine); i++) { */
    /*     if (inputLine[i] == '>' || inputLine[i] == '<') { */
    /*         ioRedirection(inputLine, inputLine[i], i); */
    /*         return; */
    /*     } */
    /* } */

    struct tokensInInput *tokenizedInput = tokenizeInput(inputLine, " ");
    /* char *cmd = tokenizedInput->tokens[0]; */

    for (int i = 0; i < tokenizedInput->noOfTokens; i++) {
        if (strcmp(tokenizedInput->tokens[i], ">") == 0 || strcmp(tokenizedInput->tokens[i], "<") == 0 || strcmp(tokenizedInput->tokens[i], ">>") == 0) {
            isIORedirection = 1;
            ioRedirPos = i;
            execute(tokenizedInput);
            return;
        }
    }

    searchCommand(tokenizedInput);
}
