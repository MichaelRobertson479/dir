#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main() {

    DIR *dir = opendir("./sample");

    if (dir == NULL) {

        printf("%s\n",strerror(errno));
    }

    struct dirent *file = readdir(dir);

    while (file != NULL) {

        printf("%s\n",file->d_name);

        file = readdir(dir);
    }

    closedir(dir);

    return 0;
}