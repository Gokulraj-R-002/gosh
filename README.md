# Shell

## Introduction
This is a simple shell program written in C that replicates most of the functionalities of the popular shells like bash and zsh.

## Instructions
* To run, compile using `make` and run `./gosh`.
* The shell starts with the current directory from which `./gosh` is run, as the HOME directory.

## Explanation of the Code

The code has been divided into the following files:

### [headers.h](headers.h)
* Contains `#include` line for all the required header files, so I can just `#include "headers.h"` in all the files.
* Contains function definitions of all the functions implemented.
* Contains definitions of structures used in the code.
* Contains `#define` values.
* Contains the declaration of all the global variables used.

### [main.c](main.c)
Contains the following functions:
* `setup()`: sets the values of global variables like username, hostname, home directory, etc.
* `shell()`: takes input from `STDIN` and calls `parseInput()` with the input command entered by the user.
* `main()`: calls `setup()` and `initializeHistory()` once, and calls `prompt()` and `shell()` infinitely many times.

### [prompt.c](prompt.c)
Contains the function `prompt()` that prints the prompt with appropriate username, hostname and current working directory.

### [parse_input.c](parse_input.c)
Contains the following functions:
* `tokenizeInput()`: tokenizes the input entered by the user to handle multiple spaces and tabs in between words.
* `parseInput()`: calls the appropriate function according to the first token of the input.

### [basic_commands.c](basic_commands.c)
Contains the following functions:
* `changeDirectory()`: implements cd command using `chdir()`.
* `echo()`: implements echo command by just printing out all the tokens in the input, except the first token (which will be the string "echo").

### [list_files.c](list_files.c)

### [system_commands.c](system_commands.c)

### [pinfo.c](pinfo.c)
* Contains a function `pinfo()` that prints out process info like pid, status, memory and executable path, by reading the files `/proc/<pid>/stat` and `/proc/<pid>/exe`.
* A pid can be passed as an argument to print the process info of the process with that pid, or by default it prints the info of the current process (which is the shell itself).

### [discover.c](discover.c)
* Contains the function `discover()` that searches for a target file/directory (depending on the flags given) in the directory given. 
* Implemented by recursively going through all the files and directories in the given path and checking if it matches the target.

### [history.c](history.c)
Contains the following main functions:
* `initializeHistory()`: initializes history by setting up the history file (`~/.gosh_history`) 
* `updateHistory()`:
* `printHistory()`:
