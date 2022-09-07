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

    // count the number of lines in the history file using system calls like read, write, lseek
    char c;
    int n = read(fdHistory, &c, 1);
    while (n > 0) {
        if (c == '\n') {
            historySize++;
        }
        n = read(fdHistory, &c, 1);
    }

    /* printf("historySize: %d\n", historySize); */

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
    /* lseek(fdHistory, 0, SEEK_END); */

    /* int bytesWritten = write(fdHistory, inputLine, strlen(inputLine)); */
    /* if (bytesWritten == -1) { */
    /*     perror("write"); */
    /* } */
    /* else if (bytesWritten > 0) { */
    /*     write(fdHistory, "\n", 1); */
    /* } */

    // write the inputLine to the history file using system calls like read, write, lseek
    // if the history file has 20 or more lines, delete the oldest line and add the new line to the end of the file
    // if the history file has less than 20 lines, add the new line to the end of the file and increment the historySize
    // if the inputLine is same as the last line in the history file, do not add it to the history file
    // if the inputLine is empty, do not add it to the history file
    

    // check if the last line in the history file is same as the inputLine
    
    /* char *lastLine = (char *) malloc (MAX_INPUT * sizeof(char)); */
    /* assert(lastLine != NULL); */
    /* char ch; */
    /* lseek(fdHistory, -2, SEEK_END); // seek to the second last character */
    /* int n = read(fdHistory, &ch, 1); */
    /* /1* strcpy(lastLine, ch); *1/ */
    /* lastLine[0] = ch; */
    /* lastLine[1] = '\0'; */
    /* while(n > 0 && ch != '\n') { */
    /*     lseek(fdHistory, -2, SEEK_CUR); */
    /*     n = read(fdHistory, &ch, 1); */
    /*     if (ch != '\n') { */
    /*         strcat(lastLine, &ch); */
    /*     } */
    /* } */
    /* reverseString(lastLine); */
    /* /1* lastLine[strlen(lastLine) - 1] = '\0'; *1/ */
    /* printf("lastLine: %s\n", lastLine); */
    /* if(strcmp(lastLine, inputLine) == 0) { */
    /*     printf("same as last line\n"); */
    /*     return; */
    /* } */

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

    /* struct tokensInInput *tokenizedHistoryFile = tokenizeInput(historyFileContents); */
    /* char *lastLine = tokenizedHistoryFile->tokens[historySize - 1]; */

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
}
