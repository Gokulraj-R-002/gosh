#include "headers.h"

void prompt() {
    char cwd[PATH_MAX];
    getcwd(cwd, PATH_MAX);

    char pathToPrint[PATH_MAX];
    strcpy(pathToPrint, cwd);
    if (strncmp(cwd, HOME, strlen(HOME)) == 0) {
        strcpy(pathToPrint, "~");
        strcat(pathToPrint, &cwd[strlen(HOME)]);
    }

    /* printf("<%s@%s:%s> ", USER, HOST, pathToPrint); */
    printf("\e[0;96m<%s@%s:\e[1;34m%s\e[0;96m> \e[0m", USER, HOST, pathToPrint);
}
