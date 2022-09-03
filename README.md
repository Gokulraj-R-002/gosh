# Shell

## Instructions
* To run, compile using `make` and run `./gosh`.

## Other explanations
### Prompt Display
* The prompt displays `<username>@<hostname>:<currentPath>`.
* `<username>` is the username of the user logged in currently.
* `<hostname>` is the system hostname.
* `<currentPath>` is the relative path of the current working directory w.r.t HOME (directory from which the shell is executed). If the current working directory is a higher directory than HOME, the absolute path is displayed.

### Basic commands
* `cd`:
    * Takes one argument.
    * Changes current working directory to the argument specified.

* `echo`:
    * Takes one argument. (multiple arguments are considered as a single argument separated with spaces)
    * Echos (prints) the argument specified to STDOUT.

* `pwd`:
    * Takes no arguments.
    * Prints the full absolute path of the current working directory.

