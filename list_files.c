#include "headers.h"

/* void listFiles(char *inputLine) { */
/*     char *path = (char *)malloc(MAX_INPUT * sizeof(char)); */
/*     path = strtok(NULL, " "); */

/*     struct dirent *files; */

/*     DIR *dir = (path == NULL) ? opendir(".") : opendir(path); */
/*     if (dir == NULL) { */
/*         printf("Directory cannot be opened!"); */
/*         return; */
/*     } */

/*     while ((files = readdir(dir)) != NULL) */
/*     printf("%s\n", files->d_name); */
/*     closedir(dir); */
/* } */

struct fileInfo {
    /* struct stat fileStat; // what is this? */
    /* struct dirent *fileInfo; */
    char *fileName;
    /* char *fileType; */
    /* char *filePermissions; */
    /* char *fileSize; */
    /* char *fileLastModified; */
    int isHidden;
    char *filePath;
};

/* int compare(struct fileInfo *a, struct fileInfo *b) { */
/*     return strcmp(a->fileName, b->fileName); */
/* } */

int compare(const void *a, const void *b) {
    struct fileInfo *ia = (struct fileInfo *)a;
    struct fileInfo *ib = (struct fileInfo *)b;
    return strcmp(ia->fileName, ib->fileName);
}

/* char *getPermissions(unsigned int mode) { */
/*     char *permissions = (char *)malloc(10 * sizeof(char)); */
/*     assert(permissions != NULL); */

/*     permissions[0] = (S_ISDIR(mode)) ? 'd' : '-'; */
/*     permissions[1] = (mode & S_IRUSR) ? 'r' : '-'; */
/*     permissions[2] = (mode & S_IWUSR) ? 'w' : '-'; */
/*     permissions[3] = (mode & S_IXUSR) ? 'x' : '-'; */
/*     permissions[4] = (mode & S_IRGRP) ? 'r' : '-'; */
/*     permissions[5] = (mode & S_IWGRP) ? 'w' : '-'; */
/*     permissions[6] = (mode & S_IXGRP) ? 'x' : '-'; */
/*     permissions[7] = (mode & S_IROTH) ? 'r' : '-'; */
/*     permissions[8] = (mode & S_IWOTH) ? 'w' : '-'; */
/*     permissions[9] = (mode & S_IXOTH) ? 'x' : '-'; */

/*     return permissions; */
/* } */

char *getPermissions(struct stat fileStat) {
    char *permissions = (char *)malloc(11 * sizeof(char));
    assert(permissions != NULL);

    if (S_ISDIR(fileStat.st_mode)) {
        permissions[0] = 'd';
    } 
    else if (S_ISREG(fileStat.st_mode)) {
        permissions[0] = '-';
    } 
    else if (S_ISLNK(fileStat.st_mode)) {
        permissions[0] = 'l';
    }
    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    return permissions;
}

void printFilesAphabetically(struct fileInfo **allFiles, int n, int *al) {
    // sorting is not working for some reason.
    /* qsort(allFiles, n, sizeof(struct fileInfo *), compare); */

    struct stat fileStat;

    // if -l flag is active, print the total on the first line
    if (al[1] == 1) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            /* fileStat = (struct stat *)malloc(sizeof(struct stat)); */
            stat(allFiles[i]->filePath, &fileStat);
            total += fileStat.st_blocks;
        }
        printf("total %d\n", total / 2);
    }

    for (int i = 0; i < n; i++) {
        if (al[1] == 1) {
            /* printf("%s\n", allFiles[i]->filePath); */
            lstat(allFiles[i]->filePath, &fileStat);
            /* stat("./test/test1", &fileStat); */
            /* if (fileStat == NULL) { */
            /*     printf("here's the problem\n"); */
            /*     printf("Error: %s\n", strerror(errno)); */
            /*     return; */
            /* } */
            /* filePermissions = getPermissions(fileStat->st_mode); */
            char *filePermissions = getPermissions(fileStat);
            /* printf("here\n"); */
            printf("%s ", filePermissions);
            /* printf("%s\t", allFiles[i]->filePath); */
            /* free(filePermissions); */

            printf("%ld ", fileStat.st_nlink);
            printf("%s ", getpwuid(fileStat.st_uid)->pw_name);
            printf("%s ", getgrgid(fileStat.st_gid)->gr_name);
            /* if (getgrgid(fileStat.st_gid)) */
            /*     printf("%-15s", getgrgid(fileStat.st_gid)->gr_name); */
            printf("%ld ", fileStat.st_size);
            printf("%ld ", fileStat.st_mtime);
        }

        // the code below takes care of printing the file name
        if (allFiles[i]->isHidden == 1) {
            if (al[0] == 0) {
                continue;
            }
            printf(".");
        }
        printf("%s\n", allFiles[i]->fileName);
    }
}

void longListFiles(char **paths, int noOfPaths, int *al) {
    struct dirent *file;
    struct fileInfo **allFiles;
    allFiles = (struct fileInfo **)malloc(MAX_INPUT * sizeof(struct fileInfo *));
    assert(allFiles != NULL);
    /* for (int i = 0; i < noOfPaths; i++) { */
    /*     stat(allFiles[i]->fileName, fileStat); // but we need to pass the full path */
        
    /*     printf("%d\n", fileStat->st_mode); */

    /*     if (allFiles[i]->isHidden == 1) { */
    /*         if (al[0] == 0) { */
    /*             continue; */
    /*         } */
    /*         printf("."); */
    /*     } */
    /*     printf("%s\n", allFiles[i]->fileName); */
    /* } */
    /* for (int i = 0; i < tokenizedInput->noOfTokens; i++) { */
    /*     struct fileInfo **allFiles = (struct fileInfo **)malloc(MAX_INPUT * sizeof(struct fileInfo *)); */
    /*     assert(allFiles != NULL); */
    /*     if (tokenizedInput->tokens[i][0] != '-') { */
    /*         stat(tokenizedInput->tokens[i], fileStat); */
    /*         printf("%d\t", fileStat->st_mode); */

    /*     } */
    /* } */

    // handle the case when noOfpaths == 0 later
    //
    for (int i = 0; i < noOfPaths; i++) {
        DIR *dir = opendir(paths[i]);
        if (dir == NULL) {
            printf("Directory cannot be opened!");
            return;
        }

        file = readdir(dir);
        int j = 0;
        while(file != NULL) {
            allFiles[j] = (struct fileInfo *)malloc(sizeof(struct fileInfo));
            assert(allFiles[j] != NULL);

            allFiles[j]->filePath = (char *)malloc(MAX_INPUT * sizeof(char));
            assert(allFiles[j]->filePath != NULL);
            /* printf("%s\t", paths[i]); */
            /* printf("here\n"); */
            /* printf("%s\n", paths[i]); */
            strcpy(allFiles[j]->filePath, paths[i]);
            strcat(allFiles[j]->filePath, "/");
            strcat(allFiles[j]->filePath, file->d_name);

            if (file->d_name[0] == '.') {
                /* file->d_name = &file->d_name[1]; */
                allFiles[j]->isHidden = 1;
                allFiles[j]->fileName = &file->d_name[1];
            }
            else {
                allFiles[j]->isHidden = 0;
                allFiles[j]->fileName = file->d_name;
            }
            /* printf("%s\n", file->d_name); */
            file = readdir(dir);
            j++;
        }

        printFilesAphabetically(allFiles, j, al);
        closedir(dir);
    }
}

void listFiles(struct tokensInInput *tokenizedInput) {
    /* char *path = (char *)malloc(MAX_INPUT * sizeof(char)); */
    /* path = strtok(NULL, " "); */
    /* char *path = (tokenizedInput->noOfTokens == 1) ? "." : tokenizedInput->tokens[1]; */

    // go through all the tokens and check if any token starts with '-'
    // if yes, then check if it is '-a' or '-l' or '-al' or '-la'
    // if yes, then set the corresponding flag
    
    int noOfPaths = tokenizedInput->noOfTokens - 1;

    int al[2] = {0}; // 0th index for -a, 1st index for -l
    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        if (tokenizedInput->tokens[i][0] == '-') {
            noOfPaths--;
            if (strcmp(tokenizedInput->tokens[i], "-a") == 0) {
                al[0] = 1;
            }
            else if (strcmp(tokenizedInput->tokens[i], "-l") == 0) {
                al[1] = 1;
            }
            else if (strcmp(tokenizedInput->tokens[i], "-al") == 0 || strcmp(tokenizedInput->tokens[i], "-la") == 0) {
                al[0] = 1;
                al[1] = 1;
            }
            else {
                printf("Invalid option: %s\n", tokenizedInput->tokens[i]);
                return;
            }
        }
    }

    char **paths = (char **)malloc(noOfPaths * sizeof(char *));
    assert(paths != NULL);
    int pathIndex = 0;
    for (int i = 1; i < tokenizedInput->noOfTokens; i++) {
        if (tokenizedInput->tokens[i][0] != '-') {
            paths[pathIndex] = tokenizedInput->tokens[i];
            pathIndex++;
        }
    }

    if (al[1] == 1) {
        longListFiles(paths, noOfPaths, al);
        return;
    }

    struct dirent *file;
    /* struct dirent **allFiles; */
    /* allFiles = (struct dirent **)malloc(MAX_INPUT * sizeof(struct dirent *)); */
    /* assert(allFiles != NULL); */

    struct fileInfo **allFiles;
    allFiles = (struct fileInfo **)malloc(MAX_INPUT * sizeof(struct fileInfo *));
    assert(allFiles != NULL);

    if (noOfPaths == 0) {
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Directory cannot be opened!");
            return;
        }

        file = readdir(dir);
        int i = 0;
        while(file != NULL) {
            // are the below line necessary
            /* allFiles[i] = (struct dirent *)malloc(sizeof(struct dirent)); */
            /* assert(allFiles[i] != NULL); */
            allFiles[i] = (struct fileInfo *)malloc(sizeof(struct fileInfo));
            assert(allFiles[i] != NULL);
            if (file->d_name[0] == '.') {
                /* file->d_name = &file->d_name[1]; */
                allFiles[i]->isHidden = 1;
                allFiles[i]->fileName = &file->d_name[1];
            }
            else {
                allFiles[i]->isHidden = 0;
                allFiles[i]->fileName = file->d_name;
            }
            /* printf("%s\n", file->d_name); */
            file = readdir(dir);
            i++;
        }

        printFilesAphabetically(allFiles, i, al);

        closedir(dir);
    }

    for (int i = 0; i < noOfPaths; i++) {
        /* DIR *dir = (paths[i] == NULL) ? opendir(".") : opendir(paths[i]); */
        DIR *dir = opendir(paths[i]);
        if (dir == NULL) {
            perror("Directory cannot be opened!");
            return;
        }

        file = readdir(dir);
        int i = 0;
        while(file != NULL) {
            // are the below line necessary
            /* allFiles[i] = (struct dirent *)malloc(sizeof(struct dirent)); */
            /* assert(allFiles[i] != NULL); */
            allFiles[i] = (struct fileInfo *)malloc(sizeof(struct fileInfo));
            assert(allFiles[i] != NULL);
            if (file->d_name[0] == '.') {
                /* file->d_name = &file->d_name[1]; */
                allFiles[i]->isHidden = 1;
                allFiles[i]->fileName = &file->d_name[1];
            }
            else {
                allFiles[i]->isHidden = 0;
                allFiles[i]->fileName = file->d_name;
            }
            /* printf("%s\n", file->d_name); */
            file = readdir(dir);
            i++;
        }

        printFilesAphabetically(allFiles, i, al);

        closedir(dir);
    }
    /* free(path); */
    /* free(path); */
    /* free(dir); */
    /* free(allFiles); */
}
