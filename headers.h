#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <limits.h>
#include <sys/wait.h>

#define size 1024

extern char USER[size]; // username
extern char HOST[size]; // hostname
extern char HOME[size]; // home directory 
extern int pid;
/* pid_t pid; */
extern char cwd[size]; // current working directory
extern char prev_wd[size]; // previous working directory


#endif
