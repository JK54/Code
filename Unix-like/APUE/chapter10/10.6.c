#include "chapter10.h"
#include <stdbool.h>

static volatile sig_atomic_t sigflag;
static sigset_t newmask;
static sigset_t oldmask;
static sigset_t zeromask;

static void sig_usr(int signo)
{
    sigflag = 1;
}

void TELL_WAIT()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        perror("signal(SIGUSR1) error");
        return;
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        perror("signal(SIGUSR2) error");
        return;
    }
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    {
        perror("");
        return;
    }
}

void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}

void WAIT_PARENT()
{
    while (sigflag == 0)
    {
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        perror("SIG_SETMASK");
        return;
    }
}

void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1);
}

void WAIT_CHILD()
{
    while (sigflag == 0)
    {
        sigsuspend(&zeromask);
    }
    sigflag = 0;

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    {
        perror("SIG_SETMASK");
        return;
    }
}

const int end = 15;

int main()
{
    int fd = open("tmp.txt", O_RDWR | O_CREAT | O_EXCL, 0644);
    unlink("tmp.txt");
    int a = 0;
    write(fd, &a, sizeof(a));
    pid_t pd;
    TELL_WAIT();
    if ((pd = fork()) < 0)
    {
        perror("");
        return 1;
    }
    else if (pd > 0)
    {
        int pa;
        while(true)
        {
            pread(fd, &pa, sizeof(pa), 0);
            if (pa >= end)
            {
                TELL_CHILD(pd);
                break;
            }
            ++pa;
            pwrite(fd, &pa, sizeof(pa), 0);
            printf("a : %d, parent\n", pa);
            TELL_CHILD(pd);
            WAIT_CHILD();
        }
    }
    else
    {
        int pb;
        pid_t pp = getppid();
        while(true)
        {
            WAIT_PARENT();
            pread(fd, &pb, sizeof pb, 0);
            if (pb >= end)
            {
                TELL_PARENT(pp);
                break;
            }
            ++pb;
            pwrite(fd, &pb, sizeof(pb), 0);
            printf("a : %d, child\n", pb);
            TELL_PARENT(pp);
        }
    }
}
