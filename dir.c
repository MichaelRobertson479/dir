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

    if (argc > 1) {
        dir = opendir(argv[1]);    
    }

    else {
        
        char dirname[100];
        printf("Enter the directory you want\n");

        fgets(dirname,100,stdin);
        printf("%s",dirname);

        dir = opendir(dirname);

        if (dir == NULL) {
            printf("%s\n",strerror(errno));
        }   
    }

    printf("stats for %s directory:\n",argv[1]);

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

                char dir_name[20];

                strcpy(dir_name, argv[1]);
                strcat(dir_name,"/");
                stat(strcat(dir_name,file->d_name),&info);

                size += info.st_size;
            }

            printf("\n");

            file = readdir(dir);
        }
 
        printf("size of regular files in directory: %ld\n", size);
    }

    closedir(dir);

    dir = opendir(".");

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