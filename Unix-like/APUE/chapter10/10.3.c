#include "chapter10.h"

static jmp_buf env_alarm;

static void sig_alarm(int signo)
{
    printf("SIGALRM\n");
    longjmp(env_alarm, 1);
}

unsigned int sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alarm) == SIG_ERR)
    {
        perror("");
        return seconds;
    }
    if (setjmp(env_alarm) == 0)
    {
        alarm(seconds);
        printf("begin sleep\n");
        pause();
    }
    return alarm(0);
}

static void sig_int(int signo)
{
    volatile int k = 0;
    printf("\nsig_int starting\n");
    for (int i = 0; i < 300000; ++i)
    {
        for (int j = 1; j < 4000; ++j)
        {
            k += i / j;
        }
    }
    printf("sig_int finished\n");
}


int main()
{
    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR)
    {
        perror("");
        return 1;
    }
    unslept = sleep2(3);
    printf("sleep2 returned : %u\n", unslept);
    return 0;
}
