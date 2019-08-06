// Copying a file 'foo' to 'bar'

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

#define BSIZE 16384

int main(){
    /* Handlers for input/output */
    int fin, fout;
    char buf[BSIZE];
    int count;

    fin = open("foo", O_RDONLY);
    if (fin < 0){
        perror("foo");
        exit(1);
    }

    fout = open("bar", O_WRONLY);
    if (fout < 0){
        perror("bar");
        exit(2);
    }

    while((count = read(fin, buf, BSIZE)) > 0){
        write(fout, buf, count);
    }

    /* Always close a file descriptor! */
    close(fin);
    close(fout);

    return 0;
}
