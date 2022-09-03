#include "headers.h"

char USER[size]; // username
char HOST[size]; // hostname
char HOME[size]; // home directory 
int pid;
char cwd[size]; // current working directory
char prevDir[size]; // previous directory

void setup() {
    gethostname(HOST, size);
    getlogin_r(USER, size);
    /* strcpy(userName, getenv("USER")); */
    getcwd(HOME, size); // set cwd as the home directory
    strcpy(cwd, HOME);
    strcpy(prevDir, cwd);

    pid = getpid();
}

void shell() {
    char *inputLine = (char *) malloc (MAX_INPUT * sizeof(char));
    /* fgets(inputLine, MAX_INPUT, stdin); */

    size_t n = MAX_INPUT;
    int cmdLength = getline(&inputLine, &n, stdin);
    inputLine[cmdLength - 1] = '\0';

    parseInput(inputLine);

}

int main() {
    setup();
    while (1) {
        prompt();
        shell();
    }

    return 0;
}
