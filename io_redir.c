#include "headers.h"

void ioRedirection(struct tokensInInput *tokenizedInput, int posInInput) {
    char *direction = tokenizedInput->tokens[posInInput];

    if (strcmp(direction, ">") == 0) {
        int fd = open(tokenizedInput->tokens[posInInput + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);
        close(fd);
    }
    else if (strcmp(direction, ">>") == 0) {
        int fd = open(tokenizedInput->tokens[posInInput + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);
        close(fd);
    }
    else if (strcmp(direction, "<") == 0) {
        int fd = open(tokenizedInput->tokens[posInInput + 1], O_RDONLY);
        dup2(fd, 0);
        close(fd);
    }
    
    // set the last two tokens to NULL as they are not needed
    tokenizedInput->tokens[posInInput] = NULL;
    tokenizedInput->tokens[posInInput + 1] = NULL;
    tokenizedInput->noOfTokens -= 2;
}
