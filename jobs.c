#include "headers.h"

struct bgProcess *bgProcesses = NULL;
int numBgProcesses = 0;

int addBgProcess(char *name, int pid) {
    struct bgProcess *newBgProcesses = realloc(bgProcesses, (numBgProcesses + 1) * sizeof(struct bgProcess));
    assert(newBgProcesses != NULL);
    /* if (newBgProcesses == NULL) { */
    /*     return 0; */
    /* } */
    bgProcesses = newBgProcesses;

    bgProcesses[numBgProcesses].num = numBgProcesses + 1;
    bgProcesses[numBgProcesses].name = name;
    bgProcesses[numBgProcesses].pid = pid;
    bgProcesses[numBgProcesses].isRunning = 1;

    numBgProcesses++;
    return numBgProcesses;
}

void stopBgProcess(int pid) {
    for (int i = 0; i < numBgProcesses; i++) {
        if (bgProcesses[i].pid == pid) {
            bgProcesses[i].isRunning = 0;
            break;
        }
    }
}

void removeBgProcess(int pid) {
    int i;
    for (i = 0; i < numBgProcesses; i++) {
        if (bgProcesses[i].pid == pid) {
            break;
        }
    }
    if (i == numBgProcesses) {
        return;
    }

    free(bgProcesses[i].name);
    for (; i < numBgProcesses - 1; i++) {
        bgProcesses[i] = bgProcesses[i + 1];
    }
    numBgProcesses--;

    struct bgProcess *newBgProcesses = realloc(bgProcesses, numBgProcesses * sizeof(struct bgProcess));
    assert(newBgProcesses != NULL);
    /* if (newBgProcesses == NULL) { */
    /*     return 0; */
    /* } */
    bgProcesses = newBgProcesses;
}

int bgProcessCompare(const void *a, const void *b) {
    struct bgProcess *bgProcessA = (struct bgProcess *)a;
    struct bgProcess *bgProcessB = (struct bgProcess *)b;
    return strcmp(bgProcessA->name, bgProcessB->name);
}

void jobs(struct tokensInInput *tokenizedInput) {

    int rsFlags[2] = {1}; // rsFlags[0] = 1 if -r is present, rsFlags[1] = 1 if -s is present

    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        if (strcmp(tokenizedInput->tokens[i], "-r") == 0) {
            rsFlags[0] = 1;
            rsFlags[1] = 0;
        }
        else if (strcmp(tokenizedInput->tokens[i], "-s") == 0) {
            rsFlags[1] = 1;
            rsFlags[0] = 0;
        }
        else if (strcmp(tokenizedInput->tokens[i], "-rs") == 0 || strcmp(tokenizedInput->tokens[i], "-sr") == 0) {
            rsFlags[0] = 1;
            rsFlags[1] = 1;
        }
        else {
            printf("jobs: invalid option\n");
            return;
        }
    }

    if (numBgProcesses == 0) {
        printf("No background processes\n");
        return;
    }
    /* qsort(bgProcesses, numBgProcesses, sizeof(struct bgProcess), bgProcessCompare); */
    for (int i = 0; i < numBgProcesses; i++) {
        /* printf("[%d] %s %s [%d]\n", bgProcesses[i].num, bgProcesses[i].isRunning ? "Running" : "Stopped", bgProcesses[i].name, bgProcesses[i].pid); */
        if ((rsFlags[0] == 1 && bgProcesses[i].isRunning == 1) || (rsFlags[1] == 1 && bgProcesses[i].isRunning == 0)) {
            printf("[%d] %s %s [%d]\n", bgProcesses[i].num, bgProcesses[i].isRunning ? "Running" : "Stopped", bgProcesses[i].name, bgProcesses[i].pid);
        }
    }
}

void sig(struct tokensInInput *tokenizedInput) {
    int processNum = atoi(tokenizedInput->tokens[1]);
    int signalNum = atoi(tokenizedInput->tokens[2]);

    if (processNum > numBgProcesses) {
        printf("No such process\n");
        return;
    }
    if (processNum == 0) {
        printf("Invalid process number\n");
        return;
    }
    kill(bgProcesses[processNum - 1].pid, signalNum);
}
