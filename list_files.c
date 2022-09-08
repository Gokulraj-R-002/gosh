#include "headers.h"

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

int compare(const void *a, const void *b) {
    const struct fileInfo *ia = (struct fileInfo *)a;
    const struct fileInfo *ib = (struct fileInfo *)b;
    return strcmp(ia->fileName, ib->fileName);
}

void printFilesAphabetically(struct fileInfo **allFiles, int n, int *al) {
    // sorting is not working for some reason.
    /* qsort(allFiles, n, sizeof(struct fileInfo *), compare); */

    struct stat fileStat;

    // if -l flag is active, print the total on the first line
    if (al[1] == 1) {
        int total = 0;
        for (int i = 0; i < n; i++) {
            if (al[0] == 0 && allFiles[i]->isHidden == 1) {
                continue;
            }
            stat(allFiles[i]->filePath, &fileStat);
            total += fileStat.st_blocks;
        }
        printf("total %d\n", total / 2);
    }

    for (int i = 0; i < n; i++) {
        if (al[0] == 0 && allFiles[i]->isHidden == 1) {
            continue;
        }
        if (al[1] == 1) {
            lstat(allFiles[i]->filePath, &fileStat);
            char *filePermissions = getPermissions(fileStat);
            printf("%s  ", filePermissions);
            printf("%ld\t", fileStat.st_nlink);
            printf("%s\t", getpwuid(fileStat.st_uid)->pw_name);
            printf("%s\t", getgrgid(fileStat.st_gid)->gr_name);
            printf("%ld\t", fileStat.st_size);

            struct tm then, now;
            char time_val[256];

            time_t present = time(0);

            localtime_r(&fileStat.st_mtime, &then);
            localtime_r(&present, &now);

            if (present - fileStat.st_mtime < 15552000)
                strftime(time_val, sizeof(time_val), "%b %e %H:%M",
                         localtime(&fileStat.st_mtime));
            else
                strftime(time_val, sizeof(time_val), "%b %e %-5Y",
                         localtime(&fileStat.st_mtime));

            printf("%s\t", time_val);
        }

        setColors(allFiles[i]->filePath);

        if (allFiles[i]->isHidden == 1) {
            printf(".");
        }
        printf("%s\n", allFiles[i]->fileName);
        resetColors();
    }
}

void listFiles(struct tokensInInput *tokenizedInput) {

    int noOfPaths = tokenizedInput->noOfTokens - 1;
    int al[2] = {0}; // 0th index for -a, 1st index for -l

    char **paths = (char **)malloc(noOfPaths * sizeof(char *));
    assert(paths != NULL);
    int pathIndex = 0;

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
        else {
            paths[pathIndex] = tokenizedInput->tokens[i];
            pathIndex++;
        }
    }

    struct dirent *file;

    struct fileInfo **allFiles;
    allFiles = (struct fileInfo **)malloc(MAX_INPUT * sizeof(struct fileInfo *));
    assert(allFiles != NULL);

    if (noOfPaths == 0) {
        paths[0] = (char *)malloc(MAX_INPUT * sizeof(char));
        assert(paths[0] != NULL);

        strcpy(paths[0], ".");
        noOfPaths = 1;
    }

    for (int i = 0; i < noOfPaths; i++) {
        DIR *dir = opendir(paths[i]);
        if (dir == NULL) {
            perror("Directory cannot be opened!");
            return;
        }

        file = readdir(dir);
        int j = 0;
        while(file != NULL) {
            allFiles[j] = (struct fileInfo *)malloc(sizeof(struct fileInfo));
            assert(allFiles[j] != NULL);

            allFiles[j]->filePath = (char *)malloc(MAX_INPUT * sizeof(char));
            assert(allFiles[j]->filePath != NULL);

            strcpy(allFiles[j]->filePath, paths[i]);
            strcat(allFiles[j]->filePath, "/");
            strcat(allFiles[j]->filePath, file->d_name);

            if (file->d_name[0] == '.') {
                allFiles[j]->isHidden = 1;
                allFiles[j]->fileName = &file->d_name[1];
            }
            else {
                allFiles[j]->isHidden = 0;
                allFiles[j]->fileName = file->d_name;
            }
            file = readdir(dir);
            j++;
        }

        printFilesAphabetically(allFiles, j, al);

        closedir(dir);
    }
    /* free(path); */
    /* free(path); */
    /* free(dir); */
    /* free(allFiles); */
}
