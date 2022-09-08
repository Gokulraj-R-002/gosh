#include "headers.h"

void setColors(char *path) {
    struct stat fileStat;
    if (stat(path, &fileStat) < 0) {
        printf("Error: Invalid path\n");
        return;
    }

    if (S_ISDIR(fileStat.st_mode)) {
        /* printf("\033[1;34m"); */
        printf(blue);
        printf(bold);
        return;
    }
    if (S_ISLNK(fileStat.st_mode)) {
        /* printf("\033[1;36m"); */
        printf(cyan);
        printf(bold);
        return;
    }
    if (fileStat.st_mode & S_IXUSR) {
        /* printf("hello\n"); */
        /* printf("\033[1;32m"); */
        printf(green);
        printf(bold);
        return;
    }
    else if (S_ISREG(fileStat.st_mode)) {
        /* printf("\033[0m"); */
        printf(white);
    }
}

void resetColors() {
    /* printf("\033[0m"); */
    printf(colorReset);
}
