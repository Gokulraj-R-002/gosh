#include "headers.h"

int fdHistory;
int historySize = 0;

void initializeHistory() {
    char *historyFile = (char *) malloc (MAX_INPUT * sizeof(char));
    assert(historyFile != NULL);

    strcpy(historyFile, HOME);
    strcat(historyFile, "/.gosh_history");

    fdHistory = open(historyFile, O_CREAT | O_RDWR, 0644);
    if (fdHistory == -1) {
        perror("open");
    }

    char c;
    int n = read(fdHistory, &c, 1);
    while (n > 0) {
        if (c == '\n') {
            historySize++;
        }
        n = read(fdHistory, &c, 1);
    }

    free(historyFile);
}

void reverseString(char *str) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void updateHistory(char *inputLine) {
    char *historyFileContents = (char *) malloc (20 * MAX_INPUT * sizeof(char));
    assert(historyFileContents != NULL);

    lseek(fdHistory, 0, SEEK_SET);
    int n = read(fdHistory, historyFileContents, 20 * MAX_INPUT);
    if (n == -1) {
        perror("read");
    }
    else {
        historyFileContents[n] = '\0';
    }

    if (historySize > 0) {
        struct tokensInInput *tokenizedHistoryFile = tokenizeInput(historyFileContents, "\n");
        char *lastLine = tokenizedHistoryFile->tokens[historySize - 1];
        // if inputLine is same as the last line in the history file, don't update the history file
        if (strcmp(lastLine, inputLine) == 0) {
            return;
        }
    }

    if (historySize >= 20) {
        lseek(fdHistory, 0, SEEK_SET);
        char c;
        int n = read(fdHistory, &c, 1);
        while (n > 0) {
            if (c == '\n') {
                break;
            }
            n = read(fdHistory, &c, 1);
        }
        lseek(fdHistory, n, SEEK_CUR);
        int bytesWritten = write(fdHistory, inputLine, strlen(inputLine));
        if (bytesWritten == -1) {
            perror("write");
        }
        else if (bytesWritten > 0) {
            write(fdHistory, "\n", 1);
        }
    }
    else {
        lseek(fdHistory, 0, SEEK_END);
        int bytesWritten = write(fdHistory, inputLine, strlen(inputLine));
        if (bytesWritten == -1) {
            perror("write");
        }
        else if (bytesWritten > 0) {
            write(fdHistory, "\n", 1);
            historySize++;
        }
    }
}

void printHistory() {
    lseek(fdHistory, 0, SEEK_SET);

    char c;
    int pos = 0;
    int n = read(fdHistory, &c, 1);
    while (n > 0) {
        if (c == '\n') {
            pos++;
        }
        if (pos >= historySize - 10) {
            printf("%c", c);
        }
        n = read(fdHistory, &c, 1);
    }
    /* char *historyFileContents = (char *) malloc (20 * MAX_INPUT * sizeof(char)); */
    /* assert(historyFileContents != NULL); */

    /* lseek(fdHistory, 0, SEEK_SET); */
    /* int n = read(fdHistory, historyFileContents, 20 * MAX_INPUT); */
    /* if (n == -1) { */
    /*     perror("read"); */
    /* } */
    /* else { */
    /*     historyFileContents[n] = '\0'; */
    /* } */

    /* if (historySize > 0) { */
    /*     struct tokensInInput *tokenizedHistoryFile = tokenizeInput(historyFileContents, "\n"); */
    /*     int start = historySize - 10; */
    /*     if (start < 0) { */
    /*         start = 0; */
    /*     } */
    /*     for (int i = start; i < historySize; i++) { */
    /*         printf("%s\n", tokenizedHistoryFile->tokens[i]); */
    /*     } */
    /* } */
}
