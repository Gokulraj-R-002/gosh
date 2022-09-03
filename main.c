#include "headers.h"
#include "prompt.h"

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


    char *cmd = (char *) malloc (MAX_INPUT * sizeof(char));
    cmd = strtok(inputLine, " ");

    if (strcmp(cmd, "exit") == 0) {
        exit(0);
    }
    else if (strcmp(cmd, "cd") == 0) {
        char *dir = (char *) malloc (MAX_INPUT * sizeof(char));
        dir = strtok(NULL, " ");

        char *arg2 = (char *) malloc (MAX_INPUT * sizeof(char));
        arg2 = strtok(NULL, " ");
        if (arg2 != NULL) {
            printf("Failed: cd: too many arguments\n");
            return;
        }

        if (dir == NULL) {
            chdir(HOME);
            strcpy(prevDir, cwd);
            /* getcwd(cwd, size); */
            strcpy(cwd, HOME);
        }
        else if (strcmp(dir, "-") == 0) {
            printf("%s\n", prevDir);
            chdir(prevDir);
            strcpy(cwd, prevDir);
            strcpy(prevDir, cwd);
            /* getcwd(cwd, size); */
        }
        else if (strcmp(dir, "~") == 0) {
            chdir(HOME);
            strcpy(prevDir, cwd);
            getcwd(cwd, size);
        }
        else {
            if (chdir(dir) != 0) {
                perror("cd");
            }
            else {
                strcpy(prevDir, cwd);
                getcwd(cwd, size);
            }
        }
    }
    else if (strcmp(cmd, "pwd") == 0) {
        printf("%s\n", cwd);
    }
    else if (strcmp(cmd, "echo") == 0) {
        char *msg = (char *) malloc (MAX_INPUT * sizeof(char));
        msg = strtok(NULL, " ");
        while(msg != NULL) {
            printf("%s ", msg);
            msg = strtok(NULL, " ");
        }
        printf("\n");
    }
    else {
        int pid = fork();
        if (pid == 0) {
            if (execvp(cmd, NULL) == -1) {
                perror("execvp");
            }
        }
        else {
            wait(NULL);
        }
    }

}

int main() {
    setup();
    while (1) {
        prompt();
        shell();
    }

    return 0;
}
