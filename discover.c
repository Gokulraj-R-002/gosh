#include "headers.h"

void discoverHelper(char *path, char *target, int *df) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char *result = (char *)malloc(MAX_INPUT * sizeof(char));
        strcpy(result, path);
        strcat(result, "/");
        strcat(result, entry->d_name);
        /* printf("Current Path: %s\nCurrent Target: %s\n", path, target); */
        if (strcmp(entry->d_name, target) == 0 || strcmp(target, "") == 0) {
            if (df[0] == 1 && entry->d_type == DT_DIR) {
                printf("%s\n", result);
            }
            if (df[1] == 1 && entry->d_type == DT_REG) {
                printf("%s\n", result);
            }
        }
        if (entry->d_type == DT_DIR) {
            discoverHelper(result, target, df);
        }
    }
}

void discover(struct tokensInInput *tokenizedInput) {
    char *path = (char *)malloc(MAX_INPUT * sizeof(char));
    assert(path != NULL);

    char *target = (char *)malloc(MAX_INPUT * sizeof(char));
    assert(target != NULL);

    int pathGiven = 0;
    int targetGiven = 0;
    int flagsGiven = 0;

    int df[2] = {0};
    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        if (tokenizedInput->tokens[i][0] == '-') {
            flagsGiven = 1;
            int len = strlen(tokenizedInput->tokens[i]);
            for (int j = 1; j < len; j++) {
                if (tokenizedInput->tokens[i][j] == 'd') {
                    df[0] = 1;
                }
                else if (tokenizedInput->tokens[i][j] == 'f') {
                    df[1] = 1;
                }
            }
        }
        else if (tokenizedInput->tokens[i][0] == '"') {
            targetGiven++;
            strcpy(target, tokenizedInput->tokens[i] + 1);
            int len = strlen(target);
            target[len - 1] = '\0';
        }
        else {
            pathGiven++;
            if (tokenizedInput->tokens[i][0] == '~') {
                strcpy(path, HOME);
                strcat(path, tokenizedInput->tokens[i] + 1);
            }
            else {
                strcpy(path, tokenizedInput->tokens[i]);
            }
        }
    }

    if (pathGiven > 1) {
        printf("Error: Too many target directories given\n");
        return;
    }
    if (targetGiven > 1) {
        printf("Error: Too many filenames given to discover\n");
        return;
    }

    if (flagsGiven == 0) {
        df[0] = 1;
        df[1] = 1;
    }
    if (pathGiven == 0) {
        strcpy(path, ".");
    }
    if (targetGiven == 0) {
        // recursively print all files and directories in path
        /* int flagForAllDF[2] = {1, 1}; */
        discoverHelper(path, "", df);
        return;
    }

    /* if (target == NULL) { */
    /*     printf("Target not specified\n"); */
    /*     return; */
    /* } */
    /* if (path == NULL) { */
    /*     strcpy(path, "."); */
    /* } */


    /* int tokenPos = 1; */
    /* if (tokenizedInput->noOfTokens == 1) { */
    /*     strcpy(path, "."); */
    /* } */
    /* else { */
    /*     strcpy(path, tokenizedInput->tokens[tokenPos]); */
    /*     tokenPos++; */
    /* } */
    /* if (tokenizedInput->tokens[tokenPos] != NULL && tokenizedInput->tokens[tokenPos][0] == '-') { */
    /*     if (strcmp(tokenizedInput->tokens[tokenPos], "-d") == 0) { */
    /*         df[0] = 1; */
    /*     } */
    /*     else if (strcmp(tokenizedInput->tokens[tokenPos], "-f") == 0) { */
    /*         df[1] = 1; */
    /*     } */
    /*     else if (strcmp(tokenizedInput->tokens[tokenPos], "-df") == 0 || strcmp(tokenizedInput->tokens[tokenPos], "-fd") == 0) { */
    /*         df[0] = 1; */
    /*         df[1] = 1; */
    /*     } */
    /*     else { */
    /*         printf("Invalid option\n"); */
    /*         return; */
    /*     } */
    /*     tokenPos++; */
    /* } */
    // -d flag means find only directories
    // -f flag means find only files
    // target stores the name of the file/directory to be searched


    // recursively search for the target file/directory depending on the flags in the given path
    // if the target is found, print the path to the target
    // if the target is not found, print nothing
    // if the target is a directory, print the path to the directory
    // if the target is a file, print the path to the file
    // if the target is a file and the -d flag is specified, print nothing
    // if the target is a directory and the -f flag is specified, print nothing
    // if there are multiple targets with the same name, print the path to all of them
    
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("Invalid path\n");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        char *result = (char *)malloc(MAX_INPUT * sizeof(char));
        strcpy(result, path);
        strcat(result, "/");
        strcat(result, entry->d_name);
        if (strcmp(entry->d_name, target) == 0) {
            if (df[0] == 1 && entry->d_type == DT_DIR) {
                printf("%s\n", result);
            }
            if (df[1] == 1 && entry->d_type == DT_REG) {
                printf("%s\n", result);
            }
        }
        if (entry->d_type == DT_DIR) {
            discoverHelper(result, target, df);
        }
    }
}
