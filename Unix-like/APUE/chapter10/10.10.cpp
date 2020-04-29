#include "chapter10.h"
// #include <sys/time.h>
#include <time.h>

int main()
{
    long long n = 0;
    while(true)
    {
        sleep(60);
        ++n;
        if (n % 5 == 0)
        {
            time_t raw_time;
            time(&raw_time);
            struct tm *t = localtime(&raw_time);
            mktime(t);
            printf("%d\n", t->tm_sec);
        }
    }
}
