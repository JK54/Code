#include "chapter10.h"
// #include <sys/time.h>
#include <time.h>
#include <fstream>
int main()
{
    long long n = 0;
    std::ofstream ofs("sleep.rec");
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
            ofs << t->tm_sec << std::endl;
        }
    }
}
