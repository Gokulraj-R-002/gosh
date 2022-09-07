#include "headers.h"

void pinfo(struct tokensInInput *tokenizedInput) {
    pid_t pid;
    if (tokenizedInput->noOfTokens == 1) {
        pid = getpid();
    }
    else {
        pid = atoi(tokenizedInput->tokens[1]);
    }

    char *fileToRead = (char *)malloc(MAX_INPUT * sizeof(char));
    assert(fileToRead != NULL);

    sprintf(fileToRead, "/proc/%d/stat", pid);

    int fd = open(fileToRead, O_RDONLY);
    if (fd == -1) {
        printf("Error: Process not found\n");
        return;
    }

    char *buffer = (char *)malloc(600 * sizeof(char));
    assert(buffer != NULL);

    int bytesRead = read(fd, buffer, 600);
    if (bytesRead == -1) {
        printf("Error: Could not read file\n");
        return;
    }

    struct tokensInInput *tokenizedBuffer = tokenizeInput(buffer);

    char *processStatus = tokenizedBuffer->tokens[2];
    char *processVirtualMemory = tokenizedBuffer->tokens[22];
    
    // not sure if the next line works properly
    /* int isFg = (strcmp(tokenizedBuffer->tokens[39], "0") == 0) ? 1 : 0; // 1 if fg, 0 if bg */
    int isFg = (strcmp(tokenizedBuffer->tokens[7], tokenizedBuffer->tokens[0]) == 0) ? 1 : 0; // 1 if fg, 0 if bg

    sprintf(fileToRead, "/proc/%d/exe", pid);

    char *executablePath = (char *)malloc(MAX_INPUT * sizeof(char));
    assert(executablePath != NULL);

    int n = readlink(fileToRead, executablePath, MAX_INPUT);
    executablePath[n] = '\0';


    printf("pid : %d\nprocess status : %s", pid, processStatus);
    if (isFg) {
        printf("+");
    }
    printf("\nmemory : %s {Virtual Memory}\nexecutable path : %s\n", processVirtualMemory, executablePath);

    free(fileToRead);
    free(buffer);
    free(executablePath);
}
