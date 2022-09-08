#include "headers.h"

int *bgPids;

struct bgProcesses {
    int pid;
    char name[100];
};

void execute(struct tokensInInput *tokenizedInput) {
    bgPids = (int *)malloc(MAX_INPUT * sizeof(int));
    assert(bgPids != NULL);
    int bgPidsIndex = 0;

    if (tokenizedInput->tokens[tokenizedInput->noOfTokens - 1][0] == '&') {
        tokenizedInput->tokens[tokenizedInput->noOfTokens - 1] = NULL;
        tokenizedInput->noOfTokens--;
        pid_t pid = fork();
        if (pid == 0) {
            bgPids[bgPidsIndex] = getpid();
            bgPidsIndex++;
            if (execvp(tokenizedInput->tokens[0], tokenizedInput->tokens) < 0) {
                printf("Error: Command not found\n");
                exit(0);
            }
        }
        else {
            // do nothing
        }
    }
    else {
        pid_t pid = fork();
        if (pid == 0) {
            // child process
            if (execvp(tokenizedInput->tokens[0], tokenizedInput->tokens) < 0) {
                printf("Error: Command not found\n");
            }
        }
        else {
            wait(NULL);
        }
    }

}
