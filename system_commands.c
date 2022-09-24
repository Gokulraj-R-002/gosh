#include "headers.h"

char *bgProcessName;

int fgPid;

void execute(struct tokensInInput *tokenizedInput) {

    if (tokenizedInput->noOfTokens == 0) {
        return;
    }

    if (tokenizedInput->tokens[tokenizedInput->noOfTokens - 1][0] == '&') {
        // bg process
        tokenizedInput->tokens[tokenizedInput->noOfTokens - 1] = NULL;
        tokenizedInput->noOfTokens--;

        pid_t pid = fork();
        if (pid == 0) {
            // child
            if (execvp(tokenizedInput->tokens[0], tokenizedInput->tokens) < 0) {
                perror("execvp");
                exit(0);
            }
        }
        else {
            // parent
            bgProcessName = tokenizedInput->tokens[0];
            printf("[1] %d\n", pid);
        }

    }
    else {
        // fg process
        int status;
        pid_t pid = fork();
        if (pid == 0) {
            // child
            if (isIORedirection) {
                ioRedirection(tokenizedInput, ioRedirPos);
            }
            if (execvp(tokenizedInput->tokens[0], tokenizedInput->tokens) < 0) {
                perror("execvp");
                exit(0);
            }
        }
        else {
            // parent
            fgPid = pid;
            waitpid(pid, &status, WUNTRACED);
            fgPid = 0;
        }
    }
}

void bgProcessExit() {
    int wstat;
    pid_t pid;

    while(1) {
        pid = wait3 (&wstat, WNOHANG, (struct rusage *)NULL );
        if (pid == 0)
            return;
        else if (pid == -1)
            return;
        else {
            printf("\n%s with pid = %d exited normally\n", bgProcessName, pid);
        }
    }
}
