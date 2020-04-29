#include "chapter10.h"

void sig_usr(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("Received %s, value = %d\n", strsignal(signo), signo);
    }
    else if (signo == SIGUSR2)
    {
        printf("Received %s, value = %d\n", strsignal(signo), signo);
    }
    else
    {
        printf("Received %d\n", signo);
    }
}

int main()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        perror("cant's catch SIGUSR1");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        perror("cant's catch SIGUSR2");
    }
    for(;;)
    {
        pause();
    }
}
