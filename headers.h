#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <sys/wait.h>
#include <dirent.h>
#include <assert.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <time.h>

#define size 1024

// colors
#define colorReset  "\x1B[0m"
#define red  "\x1B[31m"
#define green  "\x1B[32m"
#define yellow  "\x1B[33m"
#define blue  "\x1B[34m"
#define magenta  "\x1B[35m"
#define cyan  "\x1B[36m"
#define white  "\x1B[37m"
#define bold "\x1B[1m"

struct tokensInInput {
    int noOfTokens;
    char **tokens;
};

struct fileInfo {
    char *fileName;
    int isHidden;
    char *filePath;
};


extern char USER[size]; // username
extern char HOST[size]; // hostname
extern char HOME[size]; // home directory 
extern char cwd[size]; // current working directory
extern char prevDir[size]; // previous working directory
extern int fdHistory; // file descriptor for history file

// function declarations

// functions in basic_commands.c
void changeDirectory(struct tokensInInput *tokenizedInput);
void echo(struct tokensInInput *tokenizedInput);

// function in prompt.c
void prompt();

// function in parse_input.c
void parseInput(char *inputLine);
struct tokensInInput *tokenizeInput(char *inputLine, char *delim);

// functions in list_files.c
void listFiles(struct tokensInInput *tokenizedInput);

// functions in history.c
void initializeHistory();
void updateHistory(char *inputLine);
void printHistory();

// functions in pinfo.c
void pinfo(struct tokensInInput *tokenizedInput);

// functions in discover.c
void discover(struct tokensInInput *tokenizedInput);

// functions in execute.c
void execute(struct tokensInInput *tokenizedInput);
void bgProcessExit();

// functions in colors.c
void setColors(char *path);
void resetColors();


#endif
