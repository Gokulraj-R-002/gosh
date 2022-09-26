#include "headers.h"

void ctrlC_handler() {
    if (fgPid != 0) {
        kill(fgPid, SIGINT);
        fgPid = 0;
        fgName = NULL;
        printf("\n");
        /* prompt(); */
    }
    else {
        printf("\n");
        prompt();
    }
}

void ctrlZ_handler() {
    if (fgPid != 0) {
        addBgProcess(fgName, fgPid);
        kill(fgPid, SIGTSTP);
        fgPid = 0;
        fgName = NULL;
        printf("\n");
        /* prompt(); */
    }
}

void ctrlD_handler() {
    printf("\n");
    exit(0);
}
