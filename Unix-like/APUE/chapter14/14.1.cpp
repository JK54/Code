#include "../include/myapue.h"

int main()
{
    int fd;
    if ((fd = open("test.dat", O_RDWR)) < 0)
    {
        perror("open");
        return 1;
    }
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        perror("fork");
        return 1;
    }
    else if (pid > 0)
    {
        if ((pid = fork()) < 0)
        {
            perror("fork");
            return 1;
        }
        else if (pid > 0)
        {
            pid = getpid();
            read_lock(fd, 0, SEEK_SET, 4096);
            printf("parent %d set read lock\n", static_cast<int32_t>(pid));
            sleep(10);
            unlock(fd, 0, SEEK_SET, 4096);
            printf("parent %d unlock read lock\n", static_cast<int32_t>(pid));
        }
        else
        {
            if ((pid = fork()) < 0)
            {
                perror("fork");
                return 1;
            }
            else if (pid > 0)
            {
                pid = getpid();
                while(true)
                {
                    readw_lock(fd, 0, SEEK_SET, 4096);
                    printf("son %d set read lock\n", static_cast<int32_t>(pid));
                    sleep(1);
                    unlock(fd, 0, SEEK_SET, 4096);
                    printf("son %d unlock read lock\n", static_cast<int32_t>(pid));
                }
            }
            else
            {
                pid = getpid();
                while(true)
                {
                    readw_lock(fd, 0, SEEK_SET, 4096);
                    printf("son %d set read lock\n", static_cast<int32_t>(pid));
                    sleep(1);
                    unlock(fd, 0, SEEK_SET, 4096);
                    printf("son %d unlock read lock\n", static_cast<int32_t>(pid));
                }
            }
        }
    }
    else
    {
        sleep(1);
        printf("###### son %d wait for write lock\n", static_cast<int32_t>(getpid()));
        writew_lock(fd, 0, SEEK_SET, 10);
        printf("###### son %d set write lock\n", static_cast<int32_t>(getpid()));
        sleep(5);
        unlock(fd, 0, SEEK_SET, 10);
        printf("###### son %d unlock write lock\n", static_cast<int32_t>(getpid()));
    }
}
