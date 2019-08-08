#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
    char* src, dst;
    // File descriptors
    int fin, fout;
    size_t size;

    // Input file
    fin = open("foo", O_RDONLY);
    if (fin < 0){
        perror("foo");
        exit(1);
    }
    // Getting the filesize
    size = lseek(fin, 0, SEEK_END);
    if (size < 0){
        perror("size");
        exit(2);
    }

    // man 2 mmap
    // map the file as an array of
    // records
    src = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fin,
        0
    );
    if (src == MAP_FAILED){
        perror("src");
        exit(3);
    }

    // Output file
    fout = open("bar", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fout < 0){
        perror("bar");
        exit(1);
    }

    // Truncate the output file
    if(ftruncate(fout, size) == -1){
        perror("ftruncate");
        exit(4);
    }

    dst = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        fout,
        0
    );
    if (dst == MAP_FAILED){
        perror("records");
        exit(3);
    }

    memcpy(dst, src, size);

    if(msync(dst, size, MS_SYNC) == -1){
        perror("msync");
        exit(5);
    }

    return 0;
}
