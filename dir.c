#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    DIR *dir;
    char dirname[100];

    if (argc > 1) {
        strcpy(dirname,argv[1]);
        strcat(dirname,"/");
    }

    else {        
        printf("Enter the directory you want\n");

        fgets(dirname,100,stdin);

        int i = 0;

        while (dirname[i] != '\n') {
            i++;
            //printf("%p\n",dirname);
        }

        dirname[i] = '/';
        //printf("i:%d\n",i);
    }

    printf("stats for %s directory:\n",dirname);

    dir = opendir(dirname);

    if (dir == NULL) {
        printf("%s\n",strerror(errno));
    }

    else {

        struct dirent *file = readdir(dir);

        long size = 0;

        struct stat info;

        while (file != NULL) {

            printf("%s",file->d_name);

            if (file->d_type == DT_DIR) {
                printf(" (directory)");
            }

            else if (file->d_type == DT_REG) {

                stat(strcat(dirname,file->d_name),&info);

                size += info.st_size;
            }

            printf("\n");

            file = readdir(dir);
        }
 
        printf("size of regular files in directory: %ld\n", size);
    }

    closedir(dir);

    dir = opendir("./");

    printf("stats for current directory:\n");

    struct dirent *file = readdir(dir);

    long size = 0;

    while (file != NULL) {

        printf("%s",file->d_name);

        if (file->d_type == DT_DIR) {
            printf(" (directory)");
        }

        else if (file->d_type == DT_REG) {

            struct stat info;

            stat(file->d_name,&info);

            size += info.st_size;
        }

        printf("\n");

        file = readdir(dir);
    }
 
    printf("size of regular files in directory: %ld\n", size);

    closedir(dir);

    return 0;
}