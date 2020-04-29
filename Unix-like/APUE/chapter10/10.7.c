#include "chapter10.h"

void sig_abrt(int signo)
{
    printf("Received %s\n", strsignal(signo));
}

void Abort()
{
    sigset_t mask;
    struct sigaction action;
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    if (action.sa_handler == SIG_DFL)
    {
        fflush(NULL);
    }
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    printf("Send\n");
    fflush(NULL);
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}

int main()
{
    signal(SIGABRT, sig_abrt);
    Abort();
    return 0;
}
