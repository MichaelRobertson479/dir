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
            
            struct stat info;

            stat(file->d_name,&info);

            size += info.st_size;
        }

        printf("\n");

        file = readdir(dir);
    }
 
    printf("size of regular files in directory: %d\n", size);

    closedir(dir);

    return 0;
}