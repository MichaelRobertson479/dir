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

    while (file != NULL) {

        printf("%s",file->d_name);

        if (file->d_type == 4) {
            printf(" (directory)");
        }

        printf("\n");

        file = readdir(dir);
    }

    closedir(dir);

    return 0;
}