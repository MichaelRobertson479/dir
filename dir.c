#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main() {

    DIR *dir = opendir("sample");

    printf("stats for sample directory:\n");

    if (dir == NULL) {
        printf("%s\n",strerror(errno));
    }

    struct dirent *file = readdir(dir);

    long size = 0;

    struct stat info;

    while (file != NULL) {

        printf("%s",file->d_name);

        if (file->d_type == DT_DIR) {
            printf(" (directory)");
        }

        else if (file->d_type == DT_REG) {

            char dir_name[20];

            strcpy(dir_name, "sample/");
            stat(strcat(dir_name,file->d_name),&info);

            size += info.st_size;
        }

        printf("\n");

        file = readdir(dir);
    }
 
    printf("size of regular files in directory: %d\n", size);

    closedir(dir);

    dir = opendir(".");

    printf("stats for current directory:\n");

    if (dir == NULL) {
        printf("%s\n",strerror(errno));
    }

    file = readdir(dir);

    size = 0;

    while (file != NULL) {

        printf("%s",file->d_name);

        if (file->d_type == DT_DIR) {
            printf(" (directory)");
        }

        else if (file->d_type == DT_REG) {

            struct stat info;

            stat(file->d_name,&info);

            size += info.st_size;
            printf("| file size: %ld",info.st_size);
        }

        printf("\n");

        file = readdir(dir);
    }
 
    printf("size of regular files in directory: %ld\n", size);

    closedir(dir);

    return 0;
}