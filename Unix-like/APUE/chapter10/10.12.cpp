#include <stdio.h>
#include <vector>
#include <algorithm>
#include "chapter10.h"

#define BUFFSIZE 1024 * 1024 * 8

void sig_alrm(int signo)
{
    printf("###########%s\n", strsignal(signo));
    fflush(stdout);
    sleep(1);
}

int main()
{
    std::vector<char> buf(BUFFSIZE);
    std::for_each(buf.begin(),buf.end(), [](decltype(*buf.begin()) &v)
                                           {
                                               v = 'c';
                                           });
    buf[BUFFSIZE - 1] = 'a';
    setvbuf(stdout, &buf[0], _IOFBF, buf.size());
    if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    {
        perror("");
        return 1;
    }
    alarm(1);
    fwrite(&buf[0], sizeof(char), buf.size(), stdout);
}
