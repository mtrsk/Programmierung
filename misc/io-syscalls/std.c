#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    char* buffer;
    int fd, size, count, i;

    if (argc != 3){
        printf("Not enough arguments\nUsage: %s blocksize blockcount\n", argv[0]);
        exit(1);
    };

    fd = fopen("stdio.out", "w");

    size = atoi(argv[1]);
    count = atoi(argv[2]);

    buffer = malloc(size);

    for (i=0; i<count; i++){
        fwrite(buffer, size, 1, fd);
    };

    /* Always close the file! */
    close(fd);

    return 0;
};
