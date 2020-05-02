#include "../include/myapue.h"

int main()
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("pipe");
        return 1;
    }
    fcntl(fd[1], F_SETFL, O_NONBLOCK);
    for(int n = 0;;)
    {
        if (write(fd[1], "a", 1) != 1)
        {
            printf("pipe capacity = %d\n", n);
            break;
        }
        ++n;
    }
}
