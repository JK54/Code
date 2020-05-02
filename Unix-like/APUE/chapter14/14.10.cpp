#include "../include/myapue.h"
#define COPYINCR (1024 * 1024 * 1024)

int main()
{
    int fdin, fdout;

    if ((fdin = open("raw_input.dat", O_RDONLY)) < 0)
    {
        perror("open");
        return 1;
    }
    if ((fdout = open("out.dat", O_RDWR | O_CREAT | O_TRUNC | O_EXCL, 0644)) < 0)
    {
        perror("open");
        return 1;
    }
    if (ftruncate(fdout, COPYINCR) < 0)
    {
        perror("ftruncate");
        return 1;
    }
    void *src;
    if ((src = mmap(nullptr, COPYINCR, PROT_READ, MAP_SHARED, fdin, SEEK_SET)) == MAP_FAILED) 
    {
        perror("mmap");
        return 1;
    }
    void *dst;
    if ((dst = mmap(nullptr, COPYINCR, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, SEEK_SET)) == MAP_FAILED) 
    {
        perror("mmap");
        return 1;
    }
    close(fdin);
    close(fdout);
    memcpy(dst, src, COPYINCR);
    munmap(src, COPYINCR);
    munmap(dst, COPYINCR);
    return 0;
}
