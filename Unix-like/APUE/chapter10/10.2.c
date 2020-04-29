#include "chapter10.h"

int sig2str(int signo, char *str)
{
    if (signo < 1 || signo > 31)
    {
        return -1;
    }
    char *buf = strsignal(signo);
    int n = strlen(buf);
    memcpy(str, buf, n);
    return strlen(str);
}

int main()
{
    char buf[128];
    if (sig2str(SIGUSR2, buf) > 0)
    {
        printf("%s\n", buf);
    }
}
