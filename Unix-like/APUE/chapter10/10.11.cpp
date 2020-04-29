#include "chapter10.h"
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>
#define BUFFSIZE 100

void sig_intr(int signo)
{
    if (signo == SIGXFSZ)
    {
        printf("######################## %s\n", strsignal(SIGXFSZ));
    }
}

int main()
{
    int n = BUFFSIZE;
    char buf[BUFFSIZE];
    if (signal(SIGXFSZ, sig_intr) == SIG_ERR)
    {
        perror("");
        return 1;
    }
    struct rlimit newrp;
    getrlimit(RLIMIT_FSIZE, &newrp);
    newrp.rlim_cur = 1024;
    if (setrlimit(RLIMIT_FSIZE, &newrp) < 0)
    {
        perror("");
        return 1;
    }
    while((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
    {
        int this_wr = write(STDOUT_FILENO, buf, n);
        n -= this_wr;
        while (n > 0)
        {
            this_wr = write(STDOUT_FILENO, buf, n);
            printf("write %d bytes\n", this_wr);
            n -= this_wr;
        }
    }
    if (n < 0)
    {
        printf("read error\n");
        return 1;
    }
    return 0;
}
