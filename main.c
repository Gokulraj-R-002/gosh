#include "headers.h"

char USER[size]; // username
char HOST[size]; // hostname
char HOME[size]; // home directory 
char cwd[size]; // current working directory
char prevDir[size]; // previous directory

void setup() {
    gethostname(HOST, size);
    getlogin_r(USER, size);
    getcwd(HOME, size); // set cwd as the home directory
    strcpy(cwd, HOME);
    strcpy(prevDir, cwd);

}

void shell() {
    char *inputLine = (char *) malloc (MAX_INPUT * sizeof(char));
    assert(inputLine != NULL);

    size_t n = MAX_INPUT;
    int cmdLength = getline(&inputLine, &n, stdin);
    inputLine[cmdLength - 1] = '\0';

    updateHistory(inputLine);

    parseInput(inputLine);

}

int main() {
    setup();
    initializeHistory();
    while (1) {
        prompt();
        shell();
    }
    close(fdHistory);

    return 0;
}
