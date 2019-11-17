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

    if (dir == NULL) {

        printf("%s\n",strerror(errno));
    }

    struct dirent *file = readdir(dir);

    int size = 0;

    while (file != NULL) {

        printf("%s",file->d_name);

        if (file->d_type == DT_DIR) {
            printf(" (directory)");
        }

        else if (file->d_type == DT_REG) {
            
            int i = open(file->d_name);

            if (i == -1) {
                printf("%s\n",strerror(errno));
            }

            struct stat info;

            stat(i,&info);

            size += info.st_size;

            close(i);
        }

        printf("\n");

        printf("size of regular files in directory: %d\n", size);

        file = readdir(dir);
    }

    closedir(dir);

    return 0;
}