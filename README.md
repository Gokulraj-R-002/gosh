# Shell

## Introduction
This is a simple shell program written in C that replicates most of the functionalities of the popular shells like bash and zsh.

## Instructions
* To run, compile using `make` and run `./gosh`.
* The shell starts with the current directory (from which `./gosh` is run) as the HOME directory.

## Extension of Assignment-2

### Signal Handling
* `Ctrl-c` kills the current foreground process using the SIGINT signal.
* `Ctrl-z` send the current foreground process to background using the SIGTSTP signal.
* `Ctrl-d` logs out of the shell and goes back to the shell from where `./gosh` is run. Tried implementing using SIGQUIT signal but not working properly.

### I/O Redirection
* Handled `>`, `>>` and `<` operators in the input by opening (in the child process) the corresponding input/output file, and using `dup2()` function to redirect all the contents from STDOUT/STDIN to the file opened.

### Background Jobs
* A dynamically allocated array is maintained to store the info of the background processes.
* `jobs` command prints the background jobs with their pid and other info. Options: `-r` prints only the running processes, `-s` prints only the stopped processes.
* `sig` command takes two arguments `process number` and `signal number`. It send the corresponding signal to the process with `process number`.
