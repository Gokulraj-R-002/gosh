#include "headers.h"

int main () {
    int size = 1024;
    char USER[size]; // username
    char HOST[size]; // hostname
    char HOME[size]; // home directory 
    int pid;
    /* pid_t pid; */

    gethostname(HOST, size);
    getlogin_r(USER, size);
    /* strcpy(userName, getenv("USER")); */
    getcwd(HOME, size); // set cwd as the home directory

    pid = getpid();

    /* printf("%d\n", pid); */

    printf("<%s@%s:~>:", USER, HOST);
    /* printf("\e[0;96m<%s@%s:\e[1;34m%s\e[0;96m> \e[0m", USER, HOST, HOME); */

    return 0;
}
